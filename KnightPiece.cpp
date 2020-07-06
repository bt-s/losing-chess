#include "KnightPiece.h"
#include "ChessPiece.h"
#include "ChessBoard.h"

KnightPiece::KnightPiece( int x_,  int y_, bool isWhite_, Type type_,
    ChessBoard* board_) : ChessPiece(x_, y_, isWhite_, type_, board_) {}
KnightPiece::~KnightPiece() {}

char const* KnightPiece::utf_representation() {
  return this->isWhite ? "♘" : "♞";
}

char KnightPiece::latin_representation() {
  return this->isWhite ? 'N' : 'n';
}

int KnightPiece::valid_move(int x_to, int y_to) {
  int del_x = std::abs(this->x - x_to);
  int del_y = std::abs(this->y - y_to);
  if (del_x < 3 && del_y < 3 && del_x + del_y == 3) {
    std::shared_ptr<ChessPiece> cp_to = this->board->get_piece(x_to, y_to);
    if (cp_to == NULL) {
      return 1;
    } else if (cp_to->get_color() != this->get_color()) {
      return 2;
    }
  }
  return 0;
}
