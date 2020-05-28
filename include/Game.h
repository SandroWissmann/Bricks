#ifndef GAME_H
#define GAME_H

#include <cstddef>
#include <memory>

#include "GetEvent.h"
#include "Renderer.h"
#include "Level.h"

#include <vector>
#include <string>


namespace bricks{

    class Wall;
    class Brick;
    class Ball;
    class Platform;

    class Game{
    public:
        Game(std::size_t screenWidth, std::size_t screenHeight);

        void run();
    private:
        Level loadLevel(int level);

        bool ballLost();
        void handleBallCollisions();

        long long getBrickValue(const Brick& brick) const;
        void awardExtraLifeIfThresholdReached();

        std::vector<std::string> mLevelFilenames;
        Level mLevel;
        Renderer mRenderer;

        long long mScore{0};
        long long mLastExtraLifeDivisor{0};
        int mCurrentLevel{1};
        int mLifes{5};
        bool mGameOver = false;
    };

    void handleEvent(const Event& event, const Wall& leftWall, 
        const Wall& rightWall, Ball& ball, Platform& platform, bool& quit);

    void moveLeft(Platform& platform, double elapsedTimeInMS);
    void moveRight(Platform& platform, double elapsedTimeInMS);

    void delayToFramerate(double elapsedTimeInMS);

    std::vector<std::string> getLevelFilenamesFromFolder(
        const std::string& folderName);
}

#endif