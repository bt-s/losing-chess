#ifndef KINGPIECE_H
#define KINGPIECE_H

#include "ChessPiece.h"
#include <string>

class KingPiece : public ChessPiece {
  protected:
    char const* utf_representation();
    char latin_representation();
    int valid_move(int x_to, int y_to);

  public:
    KingPiece(int x, int y, bool isWhite, Type type, ChessBoard* board);
    virtual ~KingPiece();
};

#endif
