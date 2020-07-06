#include "QueenPiece.h"
#include "ChessPiece.h"
#include "ChessBoard.h"

QueenPiece::QueenPiece(int x_, int y_, bool isWhite_, Type type_,
    ChessBoard* board_) :
  ChessPiece(x_, y_, isWhite_, type_, board_),
  BishopPiece(x_, y_, isWhite_, type_, board_),
  RookPiece(x_, y_, isWhite_, type_, board_) {
}
QueenPiece::~QueenPiece() {}

char const* QueenPiece::utf_representation() {
  return this->isWhite ? "♕" : "♛";
}

char QueenPiece::latin_representation() {
  return this->isWhite ? 'Q' : 'q';
}

int QueenPiece::valid_move(int x_to, int y_to) {
  return std::max(BishopPiece::valid_move(x_to, y_to),
      RookPiece::valid_move(x_to, y_to));
}
