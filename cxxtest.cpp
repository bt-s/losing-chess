#include <cxxtest/TestSuite.h>

#include "ChessBoard.h"
#include "ChessMove.h"
#include "ChessPiece.h"
#include <sstream>
#include <memory>


class ChessTestSuite: public CxxTest::TestSuite {
  public:
    void TestBoardA(void) {
      ChessBoard chess;
      std::stringstream s;

      s << "Q..n...r" << std::endl;
      s << "........" << std::endl;
      s << "n.r....." << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s >> chess;

      std::shared_ptr<ChessPiece> cp = chess.get_piece(0, 0);
      int m1 = cp->valid_move(2, 2);
      int m2 = cp->valid_move(1, 1);
      int m3 = cp->valid_move(7, 0);
      int c1 = cp->capturing_move(2, 2);
      int c2 = cp->capturing_move(1, 1);
      int c3 = cp->capturing_move(7, 0);

      std::vector<ChessMove> v_w = chess.capturing_moves(true);
      std::vector<ChessMove> v_b = chess.capturing_moves(false);
      TS_ASSERT_EQUALS(v_w.size(), 3);
      TS_ASSERT_EQUALS(v_b.size(), 0);
      TS_ASSERT_EQUALS(m1, 2);
      TS_ASSERT_EQUALS(m2, 1);
      TS_ASSERT_EQUALS(m3, 0);
      TS_ASSERT_EQUALS(c1, true);
      TS_ASSERT_EQUALS(c2, false);
      TS_ASSERT_EQUALS(c3, false);
    }

    void TestBoardB(void) {
      ChessBoard chess;
      std::stringstream s;

      s << "Kb......" << std::endl;
      s << "nn......" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s >> chess;

      std::shared_ptr<ChessPiece> cp = chess.get_piece(0, 0);
      int m1 = cp->valid_move(1, 1);
      int m2 = cp->valid_move(2, 1);
      int c1 = cp->capturing_move(1, 1);
      int c2 = cp->capturing_move(2, 1);

      std::vector<ChessMove> v_w = chess.capturing_moves(true);
      std::vector<ChessMove> v_b = chess.capturing_moves(false);
      TS_ASSERT_EQUALS(v_w.size(), 3);
      TS_ASSERT_EQUALS(v_b.size(), 0);
      TS_ASSERT_EQUALS(m1, 2);
      TS_ASSERT_EQUALS(m2, 0);
      TS_ASSERT_EQUALS(c1, true);
      TS_ASSERT_EQUALS(c2, false);
    }

    void TestBoardC(void) {
      ChessBoard chess;
      std::stringstream s;

      s << "R..n...." << std::endl;
      s << "bn......" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s >> chess;

      std::shared_ptr<ChessPiece> cp = chess.get_piece(0, 0);
      int m1 = cp->valid_move(0, 1);
      int m2 = cp->valid_move(1, 0);
      int m3 = cp->valid_move(4, 0);
      int c1 = cp->capturing_move(0, 1);
      int c2 = cp->capturing_move(1, 0);
      int c3 = cp->capturing_move(4, 0);

      std::vector<ChessMove> v_w = chess.capturing_moves(true);
      std::vector<ChessMove> v_b = chess.capturing_moves(false);
      TS_ASSERT_EQUALS(v_w.size(), 2);
      TS_ASSERT_EQUALS(v_b.size(), 0);
      TS_ASSERT_EQUALS(m1, 2);
      TS_ASSERT_EQUALS(m2, 1);
      TS_ASSERT_EQUALS(m3, 0);
      TS_ASSERT_EQUALS(c1, true);
      TS_ASSERT_EQUALS(c2, false);
      TS_ASSERT_EQUALS(c3, false);
    }

    void TestBoardD(void) {
      ChessBoard chess;
      std::stringstream s;

      s << "B..n...." << std::endl;
      s << "bn......" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s >> chess;

      std::vector<ChessMove> v_w = chess.capturing_moves(true);
      std::vector<ChessMove> v_b = chess.capturing_moves(false);
      TS_ASSERT_EQUALS(v_w.size(), 1);
      TS_ASSERT_EQUALS(v_b.size(), 0);
    }

    void TestBoardE(void) {
      ChessBoard chess;
      std::stringstream s;

      s << "N..n...." << std::endl;
      s << "bnp....." << std::endl;
      s << ".p......" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s >> chess;

      std::vector<ChessMove> v_w = chess.capturing_moves(true);
      std::vector<ChessMove> v_b = chess.capturing_moves(false);
      TS_ASSERT_EQUALS(v_w.size(), 2);
      TS_ASSERT_EQUALS(v_b.size(), 0);
    }

    void TestBoardF(void) {
      ChessBoard chess;
      std::stringstream s;

      s << "........" << std::endl;
      s << "......p." << std::endl;
      s << ".......R" << std::endl;
      s << "..npn..." << std::endl;
      s << "...P...." << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s >> chess;

      std::shared_ptr<ChessPiece> cp = chess.get_piece(6, 1);
      int m1 = cp->valid_move(7, 2);
      int m2 = cp->valid_move(6, 0);
      int m3 = cp->valid_move(0, 0);

      std::vector<ChessMove> v_w = chess.capturing_moves(true);
      std::vector<ChessMove> v_b = chess.capturing_moves(false);
      TS_ASSERT_EQUALS(v_w.size(), 2);
      TS_ASSERT_EQUALS(v_b.size(), 1);
      TS_ASSERT_EQUALS(m1, 2);
      TS_ASSERT_EQUALS(m2, 1);
      TS_ASSERT_EQUALS(m3, 0);
    }

    void TestBoardG(void) {
      ChessBoard chess;
      std::stringstream s;

      s << "........" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << ".r......" << std::endl;
      s << ".p......" << std::endl;
      s << "...P...n" << std::endl;
      s << "......P." << std::endl;
      s << ".N...B.." << std::endl;
      s >> chess;

      std::vector<ChessMove> v_w = chess.capturing_moves(true);
      std::vector<ChessMove> v_b = chess.capturing_moves(false);
      TS_ASSERT_EQUALS(v_w.size(), 1);
      TS_ASSERT_EQUALS(v_b.size(), 0);
    }

    void TestBoardH(void) {
      ChessBoard chess;
      std::stringstream s;

      s << ".....Q.." << std::endl;
      s << "...q...." << std::endl;
      s << "......Q." << std::endl;
      s << "q......." << std::endl;
      s << ".......Q" << std::endl;
      s << ".q......" << std::endl;
      s << "....Q..." << std::endl;
      s << "..q....." << std::endl;
      s >> chess;

      std::vector<ChessMove> v_w = chess.capturing_moves(true);
      std::vector<ChessMove> v_b = chess.capturing_moves(false);
      TS_ASSERT_EQUALS(v_w.size(), 0);
      TS_ASSERT_EQUALS(v_b.size(), 0);
    }

    void TestBoardI(void) {
      ChessBoard chess;
      std::stringstream s;

      s << "rnbqkbnr" << std::endl;
      s << "pppppppp" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << "PPPPPPPP" << std::endl;
      s << "RNBQKBNR" << std::endl;
      s >> chess;

      std::vector<ChessMove> v_w = chess.capturing_moves(true);
      std::vector<ChessMove> v_b = chess.capturing_moves(false);
      TS_ASSERT_EQUALS(v_w.size(), 0);
      TS_ASSERT_EQUALS(v_b.size(), 0);
    }

    void TestBoardJ(void) {
      ChessBoard chess;
      std::stringstream s;

      s << "rnbqkbnr" << std::endl;
      s << "pppppppp" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << ".....P.." << std::endl;
      s << "........" << std::endl;
      s << "PPPPP.PP" << std::endl;
      s << "RNBQKBNR" << std::endl;
      s >> chess;

      std::vector<ChessMove> v_w = chess.capturing_moves(true);
      std::vector<ChessMove> v_b = chess.capturing_moves(false);
      TS_ASSERT_EQUALS(v_w.size(), 0);
      TS_ASSERT_EQUALS(v_b.size(), 0);
    }

    void TestBoardK(void) {
      ChessBoard chess;
      std::stringstream s;

      s << "rnbqkbnr" << std::endl;
      s << "p.pppppp" << std::endl;
      s << "........" << std::endl;
      s << ".p......" << std::endl;
      s << "....P..." << std::endl;
      s << "........" << std::endl;
      s << "PPPP.PPP" << std::endl;
      s << "RNBQKBNR" << std::endl;
      s >> chess;

      std::vector<ChessMove> v_w = chess.capturing_moves(true);
      std::vector<ChessMove> v_b = chess.capturing_moves(false);
      TS_ASSERT_EQUALS(v_w.size(), 1);
      TS_ASSERT_EQUALS(v_b.size(), 0);
    }

    void TestBoardL(void) {
      ChessBoard chess;
      std::stringstream s;

      s << "........" << std::endl;
      s << ".......p" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << "Q.P..pp." << std::endl;
      s << ".....PPP" << std::endl;
      s << "......NR" << std::endl;
      s >> chess;

      std::vector<ChessMove> v_w = chess.capturing_moves(true);
      std::vector<ChessMove> v_b = chess.capturing_moves(false);
      TS_ASSERT_EQUALS(v_w.size(), 4);
      TS_ASSERT_EQUALS(v_b.size(), 3);
    }

    void TestBoardM(void) {
      ChessBoard chess;
      std::stringstream s;

      s << "........" << std::endl;
      s << ".......K" << std::endl;
      s << "......b." << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << "........" << std::endl;
      s << "k......." << std::endl;
      s >> chess;

      bool w_k_in_check = chess.king_in_check(true);
      bool b_k_in_check = chess.king_in_check(false);
      TS_ASSERT_EQUALS(w_k_in_check, true);
      TS_ASSERT_EQUALS(b_k_in_check, false);
    }
};
