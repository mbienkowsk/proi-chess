#include "gtest/gtest.h"
#include "../../src/chess/Game.h"
#include "../../src/chess/Player.h"
#include "../../src/chess/Move.h"


namespace GameUnitTest {
    TEST(Game, constructor) {
        auto game = Game();
        ASSERT_EQ(0, game.getMoveHistory().size());
        ASSERT_EQ(16, game.getCurrentPlayer()->getPieces().size());
    }
}