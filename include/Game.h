#ifndef GAME_H
#define GAME_H

#include <cstddef>
#include <memory>

#include "AudioDevice.h"
#include "GetEvent.h"
#include "Level.h"
#include "Renderer.h"

#include <string>
#include <vector>

namespace bricks {

namespace game_objects{
    class Brick;
    class Ball;
    class Platform;
    class Wall;
}

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

    long long getBrickValue(const game_objects::Brick& brick) const;
    void awardExtraLifeIfThresholdReached();

    std::vector<std::string> mLevelFilenames;
    Level mLevel;
    Renderer mRenderer;
    AudioDevice mAudioDevice;

    static constexpr auto mStartLifes{5};

    long long mHighscore;
    long long mScore{0};
    long long mLastExtraLifeDivisor{0};
    int mCurrentLevel{1};
    int mLifes{mStartLifes};
    bool mGameOver = false;
    bool mQuit = false;
    bool mPause = false;
};

long long loadHighscore();
void writeHighscore(long long highscore);

std::string makeTitle(int level, int lifes, long long score, long long highscore);

void handleEvent(const Event& event, const game_objects::Wall& leftWall,
                 const game_objects::Wall& rightWall, 
                 game_objects::Ball& ball, 
                 game_objects::Platform& platform,
                 bool& quit, bool& pause);

void moveLeft(game_objects::Platform& platform, double elapsedTimeInMS);
void moveRight(game_objects::Platform& platform, double elapsedTimeInMS);

bool allBricksAreDestroyed(const std::vector<game_objects::Brick> bricks);

void delayToFramerate(double elapsedTimeInMS);

std::vector<std::string>
getLevelFilenamesFromFolder(const std::string& folderName);
} // namespace bricks

#endif