CC=g++
FLAGS = -std=c++11 -g -Wall -pedantic
EXETEST=ChessBoard.o ChessPiece.o KingPiece.o KnightPiece.o \
		PawnPiece.o BishopPiece.o RookPiece.o QueenPiece.o  \
		Helper.o
EXE=ChessMain.o ChessBoard.o ChessPiece.o KingPiece.o KnightPiece.o \
		PawnPiece.o BishopPiece.o RookPiece.o QueenPiece.o  \
		Helper.o

# Run all tests
tests: all all_tests.out
	./all_tests.out

# Compile the test runner
all: runner.cpp
	${CC} ${FLAGS} -o all_tests.out ${EXETEST} runner.cpp

# Generate a test runner
runner.cpp: cxxtest.cpp
	cxxtestgen -o $@ --error-printer $^

chess: ${EXE}
	${CC} ${FLAGS} ${EXE} -o chess

*.o: %.cpp %.h ChessPiece.h Helper.h
	${CC} ${FLAGS} -c $<

ChessMain.o: ChessBoard.h
ChessPiece.o: ChessBoard.h
KingPiece.o: KingPiece.h
KnightPiece.o: KnightPiece.h
PawnPiece.o: PawnPiece.h
RookPiece.o: RookPiece.h
BishopPiece.o: BishopPiece.h
QueenPiece.o: QueenPiece.h BishopPiece.h RookPiece.h

.PHONY: clean
clean:
	rm -f chess *.o

