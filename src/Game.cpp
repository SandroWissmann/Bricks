#include "Game.h"

#include "Renderer.h"
#include "Level.h"
#include "TimeMeasure.h"
#include "GameObjectPhysics.h"

#include <string>
#include <iostream>

namespace bricks{

    constexpr std::size_t framesPerSecond{60};
    constexpr std::size_t msPerFrame{1000 / framesPerSecond};

    constexpr int pointsPerBrickHitpoints{100};
    constexpr int pointsForExtraLife{10000};

    Game::Game(std::size_t screenWidth, std::size_t screenHeight)
        :mLevel{loadLevel(mCurrentLevel)},mRenderer{
            Renderer{screenWidth, screenHeight, 
            static_cast<std::size_t>(mLevel.gridWidth()),
            static_cast<std::size_t>(mLevel.gridHeight())
            }
        }
    {
    }

    void Game::run()
    {
        std::chrono::time_point<std::chrono::high_resolution_clock> timepoint1;
        std::chrono::time_point<std::chrono::high_resolution_clock> timepoint2;

        while(true) {
            timepoint1 = getCurrentTime();

            mRenderer.render(mLevel);

            auto event = getEvent();

            bool quit = false;
            handleEvent(event, mLevel.leftWall(), mLevel.rightWall(), mLevel.ball, 
                mLevel.platform, quit);
            if(quit) {
                break;
            }

            if (mLevel.ball.isActive()) {
                mLevel.ball.move(msPerFrame);

                if(ballLost()) {
                    --mLifes;
                    mLevel.resetBall();
                    mLevel.resetPlatform();
                    if(mLifes <= 0) {
                        mGameOver = true;
                    }
                }

                handleBallCollisions();
            }

            timepoint2 = getCurrentTime();

            delayToFramerate(getElapsedTime(timepoint1, timepoint2));
        }
    }

    Level Game::loadLevel(int /*level*/)
    {

        return readFromFile(
        "/mnt/Programmierung/Cpp/Udacity/Project/Bricks/level/1.lvl");
    }

    bool Game::ballLost()
    {
        return mLevel.ball.bottomRight().y >= mLevel.gridHeight();
    }

    void handleEvent(const Event& event, const Wall& leftWall, 
        const Wall& rightWall, Ball& ball, Platform& platform, bool& quit)
    {
                switch (event) {
        case Event::quit:
            [[fallthrough]];
        case Event::escape:
            quit = true;
            break;
        case Event::space:
            if (!ball.isActive()) {
                ball.activate();
            }
            break;
        case Event::left:
            if (interectsWithLeftX(platform, leftWall)) {
                putBeforeIntersectsWithLeftX(platform, leftWall);
            }
            else {
                moveLeft(platform, msPerFrame);
            }
            break;
        case Event::right:
            if (interectsWithRightX(platform, rightWall)) {
                putBeforeIntersectsWithRightX(platform, rightWall);
            }
            else {
                moveRight(platform, msPerFrame);
            }
            break;
        }
    }

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

    void Game::handleBallCollisions()
    {
        std::cout << "collide\n";
        if(reflect(mLevel.ball, mLevel.leftWall())) {
            std::cout << "collide left\n";
            return;
        }
        if(reflect(mLevel.ball, mLevel.rightWall())) {
            std::cout << "collide right\n";
            return;
        }   
        if(reflect(mLevel.ball, mLevel.topWall())) {
            std::cout << "collide top\n";
            return;
        }
        if(reflect(mLevel.ball, mLevel.platform))   {
            std::cout << "collide plattform\n";
            return;
        }
        for (auto& indestructibleBrick : mLevel.indestructibleBricks) {
            if (reflect(mLevel.ball, indestructibleBrick)) {
                std::cout << "collide indes brick\n";
                return;
            }
        }
        for (auto& brick : mLevel.bricks) {
            if (brick.isDestroyed()) {
                continue;
            }
            if (reflect(mLevel.ball, brick)) {
                brick.decreaseHitpoints();

                if (brick.isDestroyed()) {
                    mScore += getBrickValue(brick);
                    awardExtraLifeIfThresholdReached();
                }
                std::cout << "collide brick\n";
                return;
            }
        }
        std::cout << "collide noting\n";
    }

    long long Game::getBrickValue(const Brick& brick) const
    {
        return pointsPerBrickHitpoints * brick.startHitpoints() * mCurrentLevel;
    }

    void Game::awardExtraLifeIfThresholdReached()
    {
        auto extraLifeDivisor = 
            static_cast<long long>(mScore / pointsForExtraLife);
        if(extraLifeDivisor != mLastExtraLifeDivisor){
            ++mLifes;
            mLastExtraLifeDivisor = extraLifeDivisor;
        }
    }

    void delayToFramerate(double elapsedTimeInMS)
    {
        if (elapsedTimeInMS < msPerFrame) {
            wait(std::chrono::milliseconds{
                static_cast<int>(msPerFrame - elapsedTimeInMS)});
        }
    }
}