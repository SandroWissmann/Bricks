#include "Renderer.h"

#include "GameObjectPhysics.h"
#include "GetEvent.h"
#include "Level.h"
#include "OperatorDegree.h"
#include "TimeMeasure.h"

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

using namespace bricks;

void moveLeft(Platform& platform, double elapsedTimeInMS)
{
    if (auto velocity = platform.velocity(); velocity > 0) {
        velocity *= -1;
        platform.setVelocity(velocity);
    }
    platform.move(elapsedTimeInMS);
}

void moveRight(Platform& platform, double elapsedTimeInMS)
{
    if (auto velocity = platform.velocity(); velocity < 0) {
        velocity *= -1;
        platform.setVelocity(velocity);
    }
    platform.move(elapsedTimeInMS);
}

int main()
{
    constexpr std::size_t screenWidth{780};
    constexpr std::size_t screenHeight{540};
    constexpr std::size_t boardWith{26};
    constexpr std::size_t boardHeight{18};
    constexpr std::size_t framesPerSecond{60};

    constexpr std::size_t mSPerFrame{1000 / framesPerSecond};

    Renderer renderer{screenWidth, screenHeight, boardWith, boardHeight};

    auto level = bricks::readFromFile(
        "/mnt/Programmierung/Cpp/Udacity/Project/Bricks/level/5.lvl");

    std::chrono::time_point<std::chrono::high_resolution_clock> t1;
    std::chrono::time_point<std::chrono::high_resolution_clock> t2;
    double elapsedTimeInMS{0.0};

    while (true) {
        t1 = getCurrentTime();

        renderer.render(level);

        auto event = getEvent();
        if (event == Event::quit) {
            return 0;
        }

        switch (event) {
        case Event::quit:
            [[fallthrough]];
        case Event::escape:
            return 0;
        case Event::space:
            if (!level.ball.isActive()) {
                level.ball.activate();
            }
            break;
        case Event::left:
            if (interectsWithLeftX(level.platform, level.leftWall())) {
                putBeforeIntersectsWithLeftX(level.platform, level.leftWall());
            }
            else {
                moveLeft(level.platform, mSPerFrame);
            }
            break;
        case Event::right:
            if (interectsWithRightX(level.platform, level.rightWall())) {
                putBeforeIntersectsWithRightX(level.platform,
                                              level.rightWall());
            }
            else {
                moveRight(level.platform, mSPerFrame);
            }
            break;
        }

        if (level.ball.isActive()) {
            level.ball.move(mSPerFrame);
        }

        t2 = getCurrentTime();
        elapsedTimeInMS = getElapsedTime(t1, t2);

        if (elapsedTimeInMS < mSPerFrame) {
            wait(std::chrono::milliseconds{
                static_cast<int>(mSPerFrame - elapsedTimeInMS)});
        }
    }
}