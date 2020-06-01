#ifndef GAME_H
#define GAME_H

#include <cstddef>
#include <memory>

#include "AudioDevice.h"
#include "Level.h"
#include "Renderer.h"
#include "InputHandler.h"

#include <string>
#include <vector>

namespace bricks {

namespace game_objects {
class Brick;
class Ball;
class Platform;
class Wall;
} // namespace game_objects

class Game {
public:
    Game(std::size_t screenWidth, std::size_t screenHeight);

    void run();

private:
    void runLevel();

    bool beatGame();
    void increaseDifficulty();
    Level loadLevel(int levelIDX);

    void updateValuesInTitleBar();

    bool ballLost();
    void handleBallCollisions();

    long long getBrickValue(const game_objects::Brick& brick) const;
    void awardExtraLifeIfThresholdReached();

    std::vector<std::string> mLevelFilenames;
    Level mLevel;
    Renderer mRenderer;
    InputHandler mInputHandler;
    AudioDevice mAudioDevice;
    GameParameter mParameter;

    static constexpr auto mStartLifes{5};

    long long mHighscore;
    long long mScore{0};
    long long mLastExtraLifeDivisor{0};
    int mCurrentLevelIDX{1};
    int mLifes{mStartLifes};
    bool mGameOver = false;
};

long long loadHighscore();
void writeHighscore(long long highscore);

std::string makeTitle(int level, int lifes, long long score,
                      long long highscore);

bool allBricksAreDestroyed(const std::vector<game_objects::Brick> bricks);

void delayToFramerate(double elapsedTimeInMS);

std::vector<std::string>
getLevelFilenamesFromFolder(const std::string& folderName);
} // namespace bricks

#endif