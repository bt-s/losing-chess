#ifndef QUEENPIECE_H
#define QUEENPIECE_H

#include "ChessPiece.h"
#include "BishopPiece.h"
#include "RookPiece.h"

class QueenPiece : public BishopPiece, public RookPiece {
  protected:
    char const* utf_representation();
    char latin_representation();
    int valid_move(int x_to, int y_to);

  public:
    QueenPiece(int x, int y, bool isWhite, Type type, ChessBoard* board);
    virtual ~QueenPiece();
};

#endif
