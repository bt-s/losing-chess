#ifndef KNIGHTPIECE_H
#define KNIGHTPIECE_H

#include "ChessPiece.h"

class KnightPiece : public ChessPiece {
  protected:
    char const* utf_representation();
    char latin_representation();
    int valid_move( int x_to,  int y_to);

  public:
    KnightPiece(int x, int y, bool isWhite, Type type, ChessBoard* board);
    virtual ~KnightPiece();
};

#endif
