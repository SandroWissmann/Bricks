#include "Game.h"

int main()
{
    constexpr std::size_t screenWidth{780};
    constexpr std::size_t screenHeight{540};

    bricks::Game game{screenWidth, screenHeight};
    game.run();
}