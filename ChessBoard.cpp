#include "ChessBoard.h"
#include "RookPiece.h"
#include "BishopPiece.h"
#include "PawnPiece.h"
#include "KingPiece.h"
#include "QueenPiece.h"
#include "KnightPiece.h"
#include "ChessPiece.h"
#include "ChessMove.h"

#include "Matrix.h"
#include "Helper.h"

#include <memory>
#include <cmath>

void ChessBoard::move_piece(ChessMove move) {
  // Retrieve the piece to move
  std::shared_ptr<ChessPiece> cp = move.piece;

  // Change the x- and y-coordinates of the piece
  cp->x = move.x_to;
  cp->y = move.y_to;

  // Move the piece
  this->state.set_element(0, move.x_to+move.y_to*8, cp);

  // Make the original square empty (i.e. set pointer to NULL)
  this->state.set_element(0, move.x_from+move.y_from*8, NULL);
}

void ChessBoard::rewind_move_piece(ChessMove move,
 std::shared_ptr<ChessPiece> cp_removed_by_move) {
  // Retrieve the piece of the move to rewind
  std::shared_ptr<ChessPiece> cp_to_rewind = move.piece;

  // Change the x- and y-coordinates of the piece
  cp_to_rewind->x = move.x_from;
  cp_to_rewind->y = move.y_from;

  // Put the moved piece back into its original place
  this->state.set_element(0, move.x_from+move.y_from*8, cp_to_rewind);

  // Put the piece removed by the move back into place
  this->state.set_element(0, move.x_to+move.y_to*8, cp_removed_by_move);
}

void ChessBoard::ai1_make_move(bool isWhite) {
  /* Function to make a move according to the AI-1 strategy: random thinker

     - If there are no capturing moves, this AI will perform a non capturing
       at random.

     - If there are several capturing moves, the AI will perform one of them at
       random.

     - If there is a pawn promotion, a random piece will be selected.
  */
  // Get all non-capturing and capturing moves
  std::vector<ChessMove> nc_moves = non_capturing_moves(isWhite);
  std::vector<ChessMove> c_moves = capturing_moves(isWhite);

  ChessMove move;
  // If capturing moves, randomly select a move
  if (c_moves.size() > 0) {
    move = *select_random_element(c_moves.begin(), c_moves.end());
  // Otherwise randomly select a non-capturing move
  } else {
    move = *select_random_element(nc_moves.begin(), nc_moves.end());
  }

  // Make the move
  move_piece(move);

  // At the end of the board, the rPawn transforms into any of Queen, Bishop,
  // Knight, Bishop, King -- through random selection
  if ((move.piece->type == pawn && move.piece->isWhite && move.y_to == 7) ||
      (move.piece->type == pawn && !move.piece->isWhite && move.y_to == 0)) {
      // Select a random promotion piece
      int num = gen_rand_num(0, 4);
      std::shared_ptr<ChessPiece> cp_new = create_new_piece(move.x_to,
          move.y_to, move.piece->get_color(), Type(num), move.piece->board);
      // Place the promotion piece on the board
      this->state.set_element(0, move.y_to*8+move.x_to, cp_new);
  }

  switch_turn();
}

void ChessBoard::ai2_make_move(bool isWhite) {
  /* Function to make a move according to the AI-2 strategy: think one step
     ahead, but default to random

    - If there are no capturing moves
      * Check if any non-capturing move will force a capturing move for the
        opponent.
      * If not, play a random move.

    - If there are several capturing moves
      * Check if any capturing move will force a capturing move for the opponent
      * If not, play a random capturing move.

    - If there is a pawn promotion
      * If possible, pick a piece that can not capture on its next move.
      * If not possible, promote to a random piece.

  */
  // Get all non-capturing and capturing moves
  std::vector<ChessMove> nc_moves = non_capturing_moves(isWhite);
  std::vector<ChessMove> c_moves = capturing_moves(isWhite);

  bool hasMoved = false;
  ChessMove move;
  if (c_moves.size() > 0) {
    // If capturing move, see if one could force the opponent to capture one of
    // ours
    for (auto const& m: c_moves) {
      std::shared_ptr<ChessPiece> cp_to = this->get_piece(m.x_to, m.y_to);
      move_piece(m);
      if (capturing_moves(!isWhite).size() != 0) {
        move = m;
        hasMoved = true;
        break;
      } else {
        rewind_move_piece(m, cp_to);
      }
    }
    // Default to random selection
    if (!hasMoved) {
      move = *select_random_element(c_moves.begin(), c_moves.end());
      move_piece(move);
    }
  // Otherwise see if a non-capturing move could force the opponent to capture
  // one of ours
  } else {
    for (auto const& m: nc_moves) {
      std::shared_ptr<ChessPiece> cp_to = this->get_piece(m.x_to, m.y_to);
      move_piece(m);
      if (capturing_moves(!isWhite).size() != 0) {
        move = m;
        hasMoved = true;
        break;
      } else {
        rewind_move_piece(m, cp_to);
      }
    }
    // Default to random selection
    if (!hasMoved) {
      move = *select_random_element(nc_moves.begin(), nc_moves.end());
      move_piece(move);
    }
  }

  // At the end of the board, the Pawn transforms into any of Queen, Bishop,
  // Knight, Bishop, King -- preferrably one that can be captured on the next
  // move
  if ((move.piece->type == pawn && move.piece->isWhite && move.y_to == 7) ||
      (move.piece->type == pawn && !move.piece->isWhite && move.y_to == 0)) {
    bool hasBeenPromoted = false;
    // See if particular promotion could force the opponent to capture one of
    // ours
    for (int i = 0; i < 5; i++) {
      std::shared_ptr<ChessPiece> cp_new = create_new_piece(move.x_to,
          move.y_to, move.piece->get_color(), Type(i), move.piece->board);
      // Place the promotion piece on the board
      if (capturing_moves(!isWhite).size() != 0) {
        this->state.set_element(0, move.y_to*8+move.x_to, cp_new);
        hasBeenPromoted = true;
        break;
      }
    }

    // Default to random selection
    if (!hasBeenPromoted) {
      int num = gen_rand_num(0, 4);
      std::shared_ptr<ChessPiece> cp_new = create_new_piece(move.x_to,
          move.y_to, move.piece->get_color(), Type(num), move.piece->board);
      // Place the promotion piece on the board
      this->state.set_element(0, move.y_to*8+move.x_to, cp_new);
    }
  }

  switch_turn();
}

std::shared_ptr<ChessPiece> ChessBoard::create_new_piece(int x, int y,
    bool isWhite, int type, ChessBoard* board) {
  std::shared_ptr<ChessPiece> cp;
  switch (type) {
    case king:
        cp = std::make_shared<KingPiece>(x, y, isWhite, king, board);
    case queen:
        cp = std::make_shared<QueenPiece>(x, y, isWhite, queen, board);
      break;
    case bishop:
        cp = std::make_shared<BishopPiece>(x, y, isWhite, bishop, board);
      break;
    case knight:
        cp = std::make_shared<KnightPiece>(x, y, isWhite, knight, board);
      break;
    case rook:
        cp = std::make_shared<RookPiece>(x, y, isWhite, rook, board);
      break;
  }
  return cp;
}


void ChessBoard::initialise_board(Matrix<std::shared_ptr<ChessPiece>> m) {
  turn = 1;
  state = m;
}

ChessBoard & operator>>(std::istream& is, ChessBoard& board) {
  Matrix<std::shared_ptr<ChessPiece>> m(1, 64);

  char c;
  int cnt = 0;
  // Read the input stream
  c = is.get();
  while (is) {
    if (c == '\n') {
      c = is.get();
    } else {
      int x = cnt % 8;
      int y = std::floor(cnt / 8);
      // Put piece corresponding to character on the board
      switch (c) {
        case 'K':
          m.set_element(0, cnt, std::make_shared<KingPiece>(
                x, y, true, king, &board));
          break;
        case 'k':
          m.set_element(0, cnt, std::make_shared<KingPiece>(
                x, y, false, king, &board));
          break;
        case 'Q':
          m.set_element(0, cnt, std::make_shared<QueenPiece>(
                x, y, true, queen, &board));
          break;
        case 'q':
          m.set_element(0, cnt, std::make_shared<QueenPiece>(
                x, y, false, queen, &board));
          break;
        case 'N':
          m.set_element(0, cnt, std::make_shared<KnightPiece>(
                x, y, true, knight, &board));
          break;
        case 'n':
          m.set_element(0, cnt, std::make_shared<KnightPiece>(
                x, y, false, knight, &board));
          break;
        case 'P':
          m.set_element(0, cnt, std::make_shared<PawnPiece>(
                x, y, true, pawn, &board));
          break;
        case 'p':
          m.set_element(0, cnt, std::make_shared<PawnPiece>(
                x, y, false, pawn, &board));
          break;
        case 'B':
          m.set_element(0, cnt, std::make_shared<BishopPiece>(
                x, y, true, bishop, &board));
          break;
        case 'b':
          m.set_element(0, cnt, std::make_shared<BishopPiece>(
                x, y, false, bishop, &board));
          break;
        case 'R':
          m.set_element(0, cnt, std::make_shared<RookPiece>(
                x, y, true, rook, &board));
          break;
        case 'r':
          m.set_element(0, cnt, std::make_shared<RookPiece>(
                x, y, false, rook, &board));
          break;
        default:
          m.set_element(0, cnt, nullptr);
      }
      cnt++;
      c = is.get();
    }
  }
  if (cnt < 64) {
    std::cout << "Illegal size of input stream!" <<std::endl;
    exit(0);
  }

  // Initialize the board
  board.initialise_board(m);

  return board;
}

void ChessBoard::print_board() {
  std::cout << "\n    ";
  int cnt = 0;
  for (int file = 0; file <= 7; file++)
    std::cout << file << "   ";
  std::cout << std::endl;
  for (int rank=0; rank <= 7; rank++) {
    std::cout << "  +---+---+---+---+---+---+---+---+" << std::endl;
    std::cout << rank << " ";
    for (char file = 'A'; file <= 'H'; file++) {
      std::cout << '|' << " ";
      if (state.get_element(0, cnt) != NULL) {
        std::cout << state.get_element(0, cnt)->utf_representation();
      } else {
        std::cout << " ";
      }
      cnt ++;
      std::cout << " ";
    }
    std::cout << "|" << std::endl;
  }
  std::cout << "  +---+---+---+---+---+---+---+---+\n" << std::endl;
}


void ChessBoard::switch_turn() {
  turn = !turn;
}

bool ChessBoard::get_turn() {
  return turn;
}

std::shared_ptr<ChessPiece> ChessBoard::get_piece(int x, int y) {
  return state.get_element(0, x+y*8);
}

std::vector<ChessMove> ChessBoard::capturing_moves(bool isWhite) {
  std::vector<ChessMove> capturingMoves;
  int c = 0;
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      std::shared_ptr<ChessPiece> cp = this->get_piece(x, y);
      if (cp != NULL && (cp->get_color() == isWhite)) {
        std::vector<ChessMove> moves =
          this->get_piece(x, y)->capturing_moves();
        capturingMoves.insert(capturingMoves.end(), moves.begin(),
            moves.end());
      }
    }
  }
  return capturingMoves;
}

std::vector<ChessMove> ChessBoard::non_capturing_moves(bool isWhite) {
  std::vector<ChessMove> nonCapturingMoves;
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
        std::shared_ptr<ChessPiece> cp = this->get_piece(x, y);
        if (cp != NULL && (cp->get_color() == isWhite)) {
          std::vector<ChessMove> moves =
            this->get_piece(x, y)->non_capturing_moves();
          nonCapturingMoves.insert(nonCapturingMoves.end(), moves.begin(),
              moves.end());
      }
    }
  }
  return nonCapturingMoves;
}

std::vector<ChessMove> ChessBoard::possible_moves(bool isWhite) {
  std::vector<ChessMove> possible_moves = non_capturing_moves(isWhite);
  std::vector<ChessMove> c_moves = capturing_moves(isWhite);

  possible_moves.insert(possible_moves.end(), c_moves.begin(), c_moves.end());

  return possible_moves;
}

std::shared_ptr<ChessPiece> ChessBoard::find_king(bool isWhite) {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      std::shared_ptr<ChessPiece> cp = this->get_piece(x, y);
      if (cp != NULL) {
        if (cp->get_color() == isWhite && cp->get_type() == king) {
          return cp;
        }
      }
    }
  }
  return nullptr;
}

bool ChessBoard::king_in_check(bool isWhite) {
  std::shared_ptr<ChessPiece> king = find_king(isWhite);
  if (king != NULL) {
    for (int x = 0; x < 8; x++) {
      for (int y = 0; y < 8; y++) {
        std::shared_ptr<ChessPiece> cp = this->get_piece(x, y);
        if (cp != NULL && cp->get_color() != isWhite) {
          if (cp->valid_move(king->x, king->y)) {
            return true;
          }
        }
      }
    }
  }
  return false;
}

bool ChessBoard::any_valid_move(bool isWhite) {
  return possible_moves(isWhite).size() > 0 ? true : false;
}

