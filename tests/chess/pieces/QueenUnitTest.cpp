#include <vector>
#include "gtest/gtest.h"
#include "../../../src/chess/Move.h"
#include "../../../src/chess/Board.h"
#include "../common.h"


using namespace ChessUnitTestCommon;

namespace QueenUnitTest {
    TEST(Queen, getMoves_initialState) {
        auto testBoard = Board::fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
        auto whiteQueen = testBoard->getField(pos("d1"))->getPiece();
        auto blackQueen = testBoard->getField(pos("d8"))->getPiece();
        auto whiteQueenMoves = whiteQueen->getMoves();
        auto blackQueenMoves = blackQueen->getMoves();
        ASSERT_EQ(whiteQueenMoves.size(), blackQueenMoves.size());
        ASSERT_EQ(whiteQueenMoves.size(), 0);
    }

    TEST(Queen, getMovesMultipleDirectionsBlockedAndCaptures) {
        auto board = Board::fromFEN("rnbqk1nr/pppp1ppp/3b4/4p3/8/1QP5/PP1PPPPP/RNB1KBNR");
        auto queen = board->getField(pos("b3"))->getPiece();
        auto moves = queen->getMoves();

        auto expected = {
                Move(pos("b3"), pos("c2"), queen, false),
                Move(pos("b3"), pos("d1"), queen, false),
                Move(pos("b3"), pos("a3"), queen, false),
                Move(pos("b3"), pos("a4"), queen, false),
                Move(pos("b3"), pos("b4"), queen, false),
                Move(pos("b3"), pos("b5"), queen, false),
                Move(pos("b3"), pos("b6"), queen, false),
                Move(pos("b3"), pos("b7"), queen, true),
                Move(pos("b3"), pos("c4"), queen, false),
                Move(pos("b3"), pos("d5"), queen, false),
                Move(pos("b3"), pos("e6"), queen, false),
                Move(pos("b3"), pos("f7"), queen, true),
        };

        ASSERT_TRUE(isPermutation(moves, expected));
    }

    TEST(Queen, getMovesOnBoardEdge) {
        auto board = Board::fromFEN("rnbqk1nr/pppp2pp/3b1p2/4p3/Q7/2P5/PP1PPPPP/RNB1KBNR");
        auto queen = board->getField(pos("a4"))->getPiece();
        auto moves = queen->getMoves();

        auto expected = {
                Move(pos("a4"), pos("a3"), queen, false),
                Move(pos("a4"), pos("b3"), queen, false),
                Move(pos("a4"), pos("c2"), queen, false),
                Move(pos("a4"), pos("d1"), queen, false),
                Move(pos("a4"), pos("b4"), queen, false),
                Move(pos("a4"), pos("c4"), queen, false),
                Move(pos("a4"), pos("d4"), queen, false),
                Move(pos("a4"), pos("e4"), queen, false),
                Move(pos("a4"), pos("f4"), queen, false),
                Move(pos("a4"), pos("g4"), queen, false),
                Move(pos("a4"), pos("h4"), queen, false),
                Move(pos("a4"), pos("b5"), queen, false),
                Move(pos("a4"), pos("c6"), queen, false),
                Move(pos("a4"), pos("d7"), queen, true),
                Move(pos("a4"), pos("a5"), queen, false),
                Move(pos("a4"), pos("a6"), queen, false),
                Move(pos("a4"), pos("a7"), queen, true),
        };

        ASSERT_TRUE(isPermutation(moves, expected));
    }
}