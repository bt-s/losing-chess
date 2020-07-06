#ifndef CHESSMOVE_H
#define CHESSMOVE_H

#include <memory>

class ChessPiece;

struct ChessMove {
     int x_from;
     int y_from;
     int x_to;
     int y_to;

    // You can change the position of the chess piece with this pointer.
    std::shared_ptr<ChessPiece> piece;
};

#endif
