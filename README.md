# C++ Chess Implementation

This is a minimal chess game implemented in C++ whch reads a chessboard configuration as a [stringstream](http://www.cplusplus.com/reference/sstream/stringstream/).

The chess game is implemented in an object oriented manner, in which the different chess pieces all inherit from a base ChessPiece class. The chess board is represented as a 2D array that holds the chess piece objects, which makes use of a custom Matrix class.

```ChessMain.cpp``` includes an implementation of [Losing Chess](https://en.wikipedia.org/wiki/Losing_chess) with two AIs that each adopt a different strategy. Its executable (i.e. ```chess```) contains 3 experiments to test how these two strategies compare in a game of Losing Chess.

* The first AI is a random thinker. If there are no caputirng moves, it will perform a random non-capturing move. If there are multiple capturing move, the AI will choose a capturing move at random. On a pawn promotion, the AI will select a random piece.

* The second AI tries to think one step ahead, but defaults to random. If no capturing moves are possible, it checks if any non-capturing move will force the opponent to capture on of its pieces. If so, it will make this move; if not, it will make a random move. If the AI can choose between multiple capturing moves, it checks if any of them will force  a capturing move for the opponent. If so, it will make this move; if not, it defaults to making a random move. If there is a pawn promotion, it tries to pick a piece that cannot capture during its next move. If this is not possible, it will select a random piece.

The makefile can be evoked in multiple ways. Note that tests are written using [CxxTest](http://cxxtest.com/guide.html#cxxtestgen), and that the makefile relies on a test runner. After intalling CxxTest with ```$ apt install cxxtest```, the runner can be created with ```$ cxxtestgen.pl --error-printer -o runner.cpp cxxtest.cpp```.

- ```$ make chess``` creates the ```chess``` executable
- ```$ make all``` runs all tests

