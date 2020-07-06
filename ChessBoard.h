#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <memory>
#include <string>
#include <vector>
#include "Matrix.h"

class ChessPiece;
struct ChessMove;

class ChessBoard {
  private:
    Matrix<std::shared_ptr<ChessPiece>> state;
    bool turn; // White == 1

  public:
    void print_board();
    void switch_turn();
    void initialise_board(Matrix<std::shared_ptr<ChessPiece>>);
    void move_piece(ChessMove chessMove);
    void rewind_move_piece(ChessMove chessMove, std::shared_ptr<ChessPiece> cp);
    void make_move(int x_from, int y_from, int x_to, int y_to);
    void ai1_make_move(bool isWhite);
    void ai2_make_move(bool isWhite);

    bool king_in_check(bool isWhite);
    bool any_valid_move(bool isWhite);
    bool get_turn();

    std::vector<ChessMove> capturing_moves(bool isWhite);
    std::vector<ChessMove> non_capturing_moves(bool isWhite);
    std::vector<ChessMove> possible_moves(bool isWhite);

    std::shared_ptr<ChessPiece> get_piece(int x, int y);
    std::shared_ptr<ChessPiece> find_king(bool isWhite);
    std::shared_ptr<ChessPiece> create_new_piece(int x, int y,
        bool isWhite, int type, ChessBoard* board);
    std::string get_type(char c);
};

ChessBoard& operator>>(std::istream&, ChessBoard&);

#endif
