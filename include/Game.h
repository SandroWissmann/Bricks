#ifndef GAME_H
#define GAME_H

#include <cstddef>
#include <memory>

#include "GetEvent.h"
#include "Level.h"
#include "Renderer.h"

#include <string>
#include <vector>

namespace bricks {

class Wall;
class Brick;
class Ball;
class Platform;

class Game {
public:
    Game(std::size_t screenWidth, std::size_t screenHeight);

    void run();

private:
    void runLevel();

    bool beatGame();
    Level loadLevel(int level);

    void updateValuesInTitleBar();

    bool ballLost();
    void handleBallCollisions();

    long long getBrickValue(const Brick& brick) const;
    void awardExtraLifeIfThresholdReached();

    std::vector<std::string> mLevelFilenames;
    Level mLevel;
    Renderer mRenderer;

    static constexpr auto mStartLifes{5};

    long long mScore{0};
    long long mLastExtraLifeDivisor{0};
    int mCurrentLevel{1};
    int mLifes{mStartLifes};
    bool mGameOver = false;
    bool mQuitGame = false;
};

std::string makeTitle(int level, int lifes, long long score);

void handleEvent(const Event& event, const Wall& leftWall,
                 const Wall& rightWall, Ball& ball, Platform& platform,
                 bool& quit);

void moveLeft(Platform& platform, double elapsedTimeInMS);
void moveRight(Platform& platform, double elapsedTimeInMS);

bool allBricksAreDestroyed(const std::vector<Brick> bricks);

void delayToFramerate(double elapsedTimeInMS);

std::vector<std::string>
getLevelFilenamesFromFolder(const std::string& folderName);
} // namespace bricks

#endif