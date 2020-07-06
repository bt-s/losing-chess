#include "RookPiece.h"
#include "ChessPiece.h"
#include "ChessBoard.h"

#include <cmath>

RookPiece::RookPiece(int x_, int y_, bool isWhite_, Type type_,
    ChessBoard* board_) : ChessPiece(x_, y_, isWhite_, type_, board_) {}
RookPiece::~RookPiece() {}

char const* RookPiece::utf_representation() {
  return this->isWhite ? "♖" : "♜";
}

char RookPiece::latin_representation() {
  return this->isWhite ? 'R' : 'r';
}

int RookPiece::valid_move(int x_to, int y_to) {
  // The Rook can only move along its current rank or file
  if (this->x != x_to && this->y != y_to) {
    return 0;
  }
  // The Rook may not stay where it is
  if (this->x == x_to && this->y == y_to) {
    return 0;
  }

  // The Rook may not capture pieces of its own color
  std::shared_ptr<ChessPiece> cp_to = this->board->get_piece(x_to, y_to);
  if (cp_to != NULL && this->isWhite == cp_to->get_color()) {
    return 0;
  }

  // The Rook may not jump over other pieces
  int del_x = std::abs(this->x - x_to);
  int del_y = std::abs(this->y - y_to);
  if (del_x == 0) {
    if (y_to > this->y) {
      for (int it = this->y+1; it < y_to; it++) {
        if (this->board->get_piece(x_to, it) != NULL) {
          return 0;
        }
      }
    } else if (this->y > y_to) {
      for (int it = this->y-1; it > y_to; it--) {
        if (this->board->get_piece(x_to, it) != NULL) {
          return 0;
        }
      }
    }
  } else if (del_y == 0) {
    if (x_to > this->x) {
      for (int it = this->x+1; it < x_to; it++) {
        if (this->board->get_piece(it, y_to) != NULL) {
          return 0;
        }
      }
    } else if (x_to < this->x) {
      for (int it = this->x-1; it > x_to; it--) {
        if (this->board->get_piece(it, y_to) != NULL) {
          return 0;
        }
      }
    }
  }
  // Should return 2 if capturing move
  if (cp_to != NULL) {
    return 2;
  }

  return 1;
}
