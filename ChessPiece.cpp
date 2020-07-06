#include "ChessPiece.h"
#include "ChessBoard.h"
#include "ChessMove.h"

ChessPiece::ChessPiece(int x_, int y_, bool isWhite_, Type type_,
    ChessBoard* board_) : x(x_), y(y_), isWhite(isWhite_),
  type(type_), board(board_) {}
ChessPiece::~ChessPiece() {}

bool ChessPiece::get_color() {
  return this->isWhite ? 1 : 0;
}

Type ChessPiece::get_type() {
  return this->type;
}

bool ChessPiece::capturing_move(int x_to, int y_to) {
  if (!this->valid_move(x_to, y_to)) {
    return 0;
  }
  // See if, and if so what kind of piece is located at the destination square
  std::shared_ptr<ChessPiece> cp_to = this->board->get_piece(x_to, y_to);
  if (cp_to != NULL && (cp_to->get_color() != this->isWhite)) {
    return 1;
  }
}

bool ChessPiece::non_capturing_move(int x_to, int y_to) {
  return !this->capturing_move(x_to, y_to);
}

std::vector<ChessMove> ChessPiece::capturing_moves() {
  std::vector<ChessMove> moves;

  if (this != NULL) {
    for (int x=0; x < 8; x++) {
      for (int y=0; y < 8; y++) {
        if (this->valid_move(x, y)) {
          if (this->capturing_move(x, y)) {
            ChessMove move = {this->x, this->y, x, y,
              this->board->get_piece(this->x, this->y)};
            moves.push_back(move);
          }
        }
      }
    }
  }

  return moves;
}

std::vector<ChessMove> ChessPiece::non_capturing_moves() {
  std::vector<ChessMove> moves;

  for (int x=0; x < 8; x++) {
    for (int y=0; y < 8; y++) {
      if (this->valid_move(x, y)) {
        if (this->non_capturing_move(x, y)) {
          ChessMove move = {this->x, this->y, x, y,
            this->board->get_piece(this->x, this->y)};
          moves.push_back(move);
        }
      }
    }
  }

  return moves;
}

std::vector<ChessMove> ChessPiece::possible_moves() {
  std::vector<ChessMove> possible_moves = non_capturing_moves();
  std::vector<ChessMove> c_moves = capturing_moves();

  possible_moves.insert(possible_moves.end(), c_moves.begin(), c_moves.end());

  return possible_moves;
}
