#include "PawnPiece.h"
#include "ChessPiece.h"
#include "ChessBoard.h"

PawnPiece::PawnPiece(int x_, int y_, bool isWhite_, Type type_,
    ChessBoard* board_) : ChessPiece(x_, y_, isWhite_, type_, board_) {}
PawnPiece::~PawnPiece() {}

char const* PawnPiece::utf_representation() {
  return this->isWhite ? "♙" : "♟";
}

char PawnPiece::latin_representation() {
  return this->isWhite ? 'P' : 'p';
}

int PawnPiece::valid_move(int x_to, int y_to) {
  // See if, and if so what kind of piece is located at the destination square
  std::shared_ptr<ChessPiece> cp_to = this->board->get_piece(x_to, y_to);

  if (cp_to != NULL) {
    bool color_to = cp_to->get_color();
  }

  // If attempting to go straight
  if (this->x == x_to) {
    // Pawn can only go straight if there is no piece in front of it
    if (cp_to != NULL) {
      return 0;
    }

    // A pawn may not move straight backwards
    if ((this->isWhite && this->y > y_to) ||
        (!this->isWhite && this->y < y_to)) {
      return 0;
    }

    // Can move two square if in first row
    if ((this->isWhite && y == 1 && (this->y - y_to ) == -2) ||
        (!this->isWhite && y == 6 && (this->y - y_to ) == 2)) {
      if (this->board->get_piece(x_to, y_to-1) == NULL) {
        return 1;
      }
    }

    // Can always move one square
    if ((this->isWhite && (this->y - y_to ) == -1) ||
        (!this->isWhite && (this->y - y_to ) == 1)) {
      return 1;
    }
  // If attempting to go diagonally
  } else if (std::abs(this->y - y_to) == 1 && (std::abs(this->x-x_to) == 1)) {
      if (cp_to != NULL) {
        // Should return 2 if capturing move
        if (this->isWhite != cp_to->get_color()) {
          return 2;
        }
      }
  }
  return 0;
}

