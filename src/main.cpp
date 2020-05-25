#include <iostream>

#include "Renderer.h"

int main()
{
    constexpr std::size_t screenWidth{640};
    constexpr std::size_t screenHeight{640};
    constexpr std::size_t boardWith{26};
    constexpr std::size_t boardHeight{18};
    bricks::Renderer renderer{screenWidth, screenHeight, boardWith, boardHeight};

    int i = 0;
}