#include "Renderer.h"

#include "Platform.h"
#include "Ball.h"
#include "Level.h"
#include "Wall.h"

#include "OperatorDegree.h"

#include <thread>

using namespace bricks;

int main()
{
    constexpr std::size_t screenWidth{780};
    constexpr std::size_t screenHeight{540};
    constexpr std::size_t boardWith{26};
    constexpr std::size_t boardHeight{18};
    Renderer renderer{screenWidth, screenHeight, boardWith, boardHeight};

    bricks::Platform platform{
        types::Point{ (boardWith / 2.0) - 2.0 , boardHeight -1.0},
        types::Length{4.0},
        types::Width{0.5},
        types::MaxPositionX{boardWith},
        types::MaxPositionY{boardHeight},
        types::Velocity{18.0}
    };

    bricks::Ball ball{
        types::Point{boardWith / 2.0, boardHeight -2.0},
        types::Length{0.75},
        types::Width{0.75},
        types::MaxPositionX{boardWith},
        types::MaxPositionY{boardHeight},
        types::Velocity{16.0},
        types::Angle{135.0_deg},
        types::Gravity{}
    };

    std::vector<Wall> walls{
        Wall{
            types::Point{0.0, 0.0},
            types::Length{1.0},
            types::Width{boardHeight}
        },
        Wall{
            types::Point{boardWith - 1.0},
            types::Length{1.0},
            types::Width{boardHeight}
        },
        Wall{
            types::Point{1, 0},
            types::Length{ boardWith - 2.0 * 1.0},
            types::Width{1.0}
        }
    };

    bricks::Level level;

    while(true) {
        renderer.render(ball, platform, walls, level);

        std::this_thread::sleep_for(std::chrono::milliseconds{100});
    }

    int i = 0;
}