#ifndef BishopPIECE_H
#define BishopPIECE_H

#include "ChessPiece.h"

class BishopPiece : virtual public ChessPiece {
  protected:
    char const* utf_representation();
    char latin_representation();
    int valid_move(int x_to, int y_to);

  public:
    BishopPiece(int x, int y, bool isWhite, Type type, ChessBoard* board);
    virtual ~BishopPiece();
};

#endif
