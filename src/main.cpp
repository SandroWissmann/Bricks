#include "Renderer.h"

#include "Level.h"

#include "OperatorDegree.h"

#include <thread>
#include <string>

using namespace bricks;

int main()
{
    constexpr std::size_t screenWidth{780};
    constexpr std::size_t screenHeight{540};
    constexpr std::size_t boardWith{26};
    constexpr std::size_t boardHeight{18};
    Renderer renderer{screenWidth, screenHeight, boardWith, boardHeight};

    auto level = bricks::readFromFile(
        "/mnt/Programmierung/Cpp/Udacity/Project/Bricks/level/5.lvl");

    while(true) {
        renderer.render(level);

        std::this_thread::sleep_for(std::chrono::milliseconds{100});
    }

    int i = 0;
}