#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <vector>
#include <string>

#include "ChessBoard.h"
#include "Helper.h"

class ChessBoard;
struct ChessMove;

class ChessPiece {
  friend class ChessTestSuite;
  friend void ChessBoard::print_board();
  friend void ChessBoard::move_piece(ChessMove);
  friend void ChessBoard::rewind_move_piece(ChessMove,
      std::shared_ptr<ChessPiece>);
  friend bool ChessBoard::king_in_check(bool isWhite);
  friend bool ChessBoard::any_valid_move(bool isWhite);
  friend void ChessBoard::ai1_make_move(bool isWhite);
  friend void ChessBoard::ai2_make_move(bool isWhite);

  protected:
    int x, y;
    bool isWhite;
    ChessBoard* board;
    Type type;

    /**
    * Returns 0 if target square is unreachable.
    * Returns 1 if target square is reachable and empty.
    * Returns 2 if move captures a piece.
    */
    virtual int valid_move( int x_to,  int y_to) = 0;
    virtual char const* utf_representation() = 0;
    virtual char latin_representation() = 0;
  public:
    ChessPiece(int x, int y, bool isWhite, Type type, ChessBoard* board);
    virtual ~ChessPiece();
    /**
    * Checks if this move is valid for this piece and captures
    * a piece of the opposite color.
    */
    bool capturing_move(int x_to, int y_to);
    /**
    * Checks if this move is valid but does not capture a piece.
    */
    bool non_capturing_move(int x_to, int y_to);
    std::vector<ChessMove> capturing_moves();
    std::vector<ChessMove> non_capturing_moves();
    std::vector<ChessMove> possible_moves();

    bool get_color();
    Type get_type();
};

#endif
