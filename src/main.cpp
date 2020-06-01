#include "Game.h"

#include <iostream>

int main()
{
    try{
        constexpr std::size_t screenWidth{780};
        constexpr std::size_t screenHeight{540};

        bricks::Game game{screenWidth, screenHeight};
        game.run();
    }
    catch (const std::out_of_range& e) {
        std::cerr << e.what() << "\n";
        std::cin.get();
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << "\n";
        std::cin.get();
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << "\n";
        std::cin.get();
    }
    catch (...) {
        std::cerr << "unknown error " << "\n";
        std::cin.get();
    }
}