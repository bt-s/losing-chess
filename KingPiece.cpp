#include "KingPiece.h"
#include "ChessPiece.h"
#include "ChessBoard.h"
#include "ChessMove.h"

#include <cmath>

KingPiece::KingPiece(int x_, int y_, bool isWhite_, Type type_,
    ChessBoard* board_) : ChessPiece(x_, y_, isWhite_, type_, board_) {}
KingPiece::~KingPiece() {}

char const* KingPiece::utf_representation() {
  return this->isWhite ? "♔" : "♚";
}

char KingPiece::latin_representation() {
  return this->isWhite ? 'K' : 'k';
}

int KingPiece::valid_move(int x_to, int y_to) {
  int del_x = std::abs(this->x - x_to);
  int del_y = std::abs(this->y - y_to);

  // The King can only move within a certain range
  if (!((del_x + del_y) == 1 || (del_x * del_y) == 1)) {
    return 0;
  }

  std::shared_ptr<ChessPiece> cp_to = this->board->get_piece(x_to, y_to);
  // The King cannot move to a square occupied by one of its own pieces
  if (cp_to != NULL && cp_to->get_color() == this->get_color()) {
    return 0;
  }

  // The King can move to an empty square
  if (cp_to == NULL) {
    return 1;
  }

  // The King captures the opponent's piece
  return 2;
}

