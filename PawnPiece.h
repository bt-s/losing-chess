#ifndef PAWNPIECE_H
#define PAWNPIECE_H

#include "ChessPiece.h"

class PawnPiece : public ChessPiece {
  protected:
    char const* utf_representation();
    char latin_representation();
    int valid_move(int x_to, int y_to);

  public:
    PawnPiece(int x, int y, bool isWhite, Type type, ChessBoard* board);
    virtual ~PawnPiece();
};

#endif
