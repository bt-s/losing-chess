#ifndef ROOKPIECE_H
#define ROOKPIECE_H

#include "ChessPiece.h"

class RookPiece : virtual public ChessPiece {
  protected:
    char const* utf_representation();
    char latin_representation();
    int valid_move(int x_to, int y_to);

  public:
    RookPiece(int x, int y, bool isWhite, Type type, ChessBoard* board);
    virtual ~RookPiece();
};

#endif
