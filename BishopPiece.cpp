#include "BishopPiece.h"
#include "ChessPiece.h"
#include "ChessBoard.h"

BishopPiece::BishopPiece(int x_, int y_, bool isWhite_, Type type_,
    ChessBoard* board_) : ChessPiece(x_, y_, isWhite_, type_, board_) {}
BishopPiece::~BishopPiece() {}

char const* BishopPiece::utf_representation() {
  return this->isWhite ? "♗" : "♝";
}

char BishopPiece::latin_representation() {
  return this->isWhite ? 'B' : 'b';
}

int BishopPiece::valid_move(int x_to, int y_to) {
  int del_x = std::abs(this->x - x_to);
  int del_y = std::abs(this->y - y_to);

  // Bishop can only move along diagonals
  if (this->x == x_to || this->y == y_to || del_x != del_y) {
    return 0;
  }

  // Bishop may not capture pieces of its own color
  std::shared_ptr<ChessPiece> cp_to = this->board->get_piece(x_to, y_to);
  if (cp_to != NULL && this->isWhite == cp_to->get_color()) {
    return 0;
  }
  // Bishop may not jump over other pieces
  for (int it = 1; it < del_x; it++) {
    if (x_to > this->x && y_to > this->y) {
      if (this->board->get_piece(this->x + it, this->y + it) != NULL) {
        return 0;
      }
    } else if (x_to < this->x && y_to < this->y) {
      if (this->board->get_piece(this->x - it, this->y - it) != NULL) {
        return 0;
      }
    } else if (x_to > this->x && y_to < this->y) {
      if (this->board->get_piece(this->x + it, this->y - it) != NULL) {
        return 0;
      }
    } else if (x_to < this->x && y_to > this->y) {
      if (this->board->get_piece(this->x - it, this->y + it) != NULL) {
        return 0;
      }
    }
  }

  // Return 2 if capturing move
  if (cp_to != NULL) {
    return 2;
  }

  // Return 2 if nocapturing move
  return 1;
}
