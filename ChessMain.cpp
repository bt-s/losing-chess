#include "ChessBoard.h"
#include "ChessMove.h"
#include <sstream>

using namespace std;

int ai_game(ChessBoard &chess, int type=0, bool verbose=false) {
  /* Simulates a game played between two AIs

     Three types are possible:
       - Type 0: AI-1 vs. Ai-1
       - Type 1: AI-1 vs. Ai-2
       - Type 2: AI-2 vs. Ai-2

     This function returns:
       - 0 if black has won
       - 1 if white has won
       - 2 if it is a draw (300 moves)
  */
  std::string colorMap[2];
  colorMap[0] = "black";
  colorMap[1] = "white";

  int turns = 1;
  while (!(chess.possible_moves(true).size() == 0 ||
        chess.possible_moves(false).size() == 0)) {
    bool turn = chess.get_turn();
    if (verbose) {
      std::cout << "Turn " << turns << " -- " << colorMap[turn] << std::endl;
    }

    switch (type) {
      case 0:
        chess.ai1_make_move(chess.get_turn());
        break;
      case 1:
        turn ? chess.ai1_make_move(chess.get_turn()) :
          chess.ai2_make_move(chess.get_turn());
        break;
      case 2:
        chess.ai2_make_move(chess.get_turn());
        break;
    }

    if (verbose) {
      chess.print_board();
    }

    if (turns > 300) {
      if (verbose) {
        std::cout << "The game ended in a draw." << std::endl;
      }
      return 2;
    }

    turns++;
  }

  if (verbose) {
    std::cout << "It is " << colorMap[chess.get_turn()] <<
      " who won the game!" << std::endl;
  }

  return chess.get_turn();
}


ChessBoard init_board() {
  ChessBoard chess;
  stringstream s;
  s << "RNBKQBNR" << std::endl;
  s << "PPPPPPPP" << std::endl;
  s << "........" << std::endl;
  s << "........" << std::endl;
  s << "........" << std::endl;
  s << "........" << std::endl;
  s << "pppppppp" << std::endl;
  s << "rnbqkbnr" << std::endl;

  s >> chess;

  return chess;
}

void experiment(int type=0, int cnt=100) {
  std::string gameMap[3];
  gameMap[0] = "AI-1 (white) vs AI-1 (black)";
  gameMap[1] = "AI-1 (white) vs AI-2 (black)";
  gameMap[2] = "AI-2 (white) vs AI-2 (black)";

  int cnt_white_win = 0;
  int cnt_black_win = 0;
  int cnt_draw = 0;
  for (int i=0; i < cnt; i++) {
    ChessBoard chess = init_board();
    int res = ai_game(chess, type);
    switch (res) {
      case 0:
        cnt_white_win += 1;
        break;
      case 1:
        cnt_black_win += 1;
        break;
      case 2:
        cnt_draw += 1;
        break;
    }
  }

  std::cout << gameMap[type] << " / " << cnt << " games:\n\t" <<
    "White won " << cnt_white_win << " times\n\tBlack won " <<
    cnt_black_win << " times\n\tDraw " << cnt_draw << " times" << std::endl;
}

int main() {
  // AI-1 vs AI-1 (1000 times)
  experiment(0, 1000);
  // AI-1 vs AI-2 (1000 times)
  experiment(1, 1000);
  // AI-2 vs AI-2 (1000 times)
  experiment(2, 1000);


  return 0;
}
