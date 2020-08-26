#include "Game.h"

#include "game_objects/Physics.h"

#include "utility/IsNumber.h"
#include "utility/TimeMeasure.h"

#include <algorithm>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <string>

namespace bricks {

using namespace utility;

using Ball = game_objects::Ball;
using Brick = game_objects::Brick;
using GameObject = game_objects::GameObject;
using IndestructibleBrick = game_objects::IndestructibleBrick;
using Platform = game_objects::Platform;
using Wall = game_objects::Wall;

using Width = types::Width;
using Velocity = types::Velocity;
using Gravity = types::Gravity;

constexpr std::size_t framesPerSecond{60};
constexpr std::size_t msPerFrame{1000 / framesPerSecond};

constexpr int pointsPerBrickHitpoints{100};
constexpr int pointsForExtraLife{10000};

constexpr auto highscoreFilename = "highscore.dat";

constexpr double ballVelocityIncrease = 2.0;
constexpr double ballGravityIncrease = 0.5;
constexpr double platformVelocityIncrease = 2.0;
constexpr double platformWidthDecrease = 0.5;

constexpr double ballVelocityMax = 30.0;
constexpr double ballGravityMax = 5.0;
constexpr double platformVelocityMax = 28.0;
constexpr double platformWidthMin = 2.0;

Game::Game(std::size_t screenWidth, std::size_t screenHeight)
    : mLevelFilenames{getLevelFilenamesFromFolder("level")},
      mLevel{loadLevel(1)}, mRenderer{Renderer{
                                screenWidth, screenHeight,
                                static_cast<std::size_t>(mLevel.gridWidth()),
                                static_cast<std::size_t>(mLevel.gridHeight())}},
      mHighscore{loadHighscore()}
{
    updateValuesInTitleBar();
}

void Game::run()
{
    while (true) {
        runLevel();
        if (mInputHandler.isQuit()) {
            return;
        }
        if (mGameOver) {
            playGameOver(mAudioDevice);
            if (mScore > mHighscore) {
                mHighscore = mScore;
                writeHighscore(mHighscore);
            }
            mCurrentLevelIDX = 1;
            mLifes = mStartLifes;
            mGameOver = false;
            mScore = 0;
            mParameter = DifficultyParameter{};
        }
        else if (beatGame()) {
            playWinGame(mAudioDevice);
            mCurrentLevelIDX = 1;
            increaseDifficulty();
        }
        else {
            playNextLevel(mAudioDevice);
            ++mCurrentLevelIDX;
        }
        mLevel = loadLevel(mCurrentLevelIDX);
        updateValuesInTitleBar();
    }
}

void Game::runLevel()
{
    std::chrono::time_point<std::chrono::high_resolution_clock> timepoint1;
    std::chrono::time_point<std::chrono::high_resolution_clock> timepoint2;

    while (true) {
        timepoint1 = getCurrentTime();

        mRenderer.render(mLevel);

        mInputHandler.handleInput(mLevel, msPerFrame);
        if (mInputHandler.changedPauseState()) {
            mRenderer.setPaused(mInputHandler.isPaused());
        }
        if (mInputHandler.isQuit()) {
            return;
        }
        if (mInputHandler.isPaused()) {
            continue;
        }

        if (mLevel.ball.isActive()) {
            mLevel.ball.move(msPerFrame);

            if (ballLost()) {
                --mLifes;
                if (mLifes <= 0) {
                    mGameOver = true;
                    return;
                }
                playLostBall(mAudioDevice);

                updateValuesInTitleBar();
                mLevel.resetBall();
                mLevel.resetPlatform();
            }

            handleBallCollisions();
            if (allBricksAreDestroyed(mLevel.bricks)) {
                break;
            }
        }

        timepoint2 = getCurrentTime();

        delayToFramerate(getElapsedTime(timepoint1, timepoint2));
    }
}

bool Game::beatGame()
{
    return mCurrentLevelIDX >= mLevelFilenames.size();
}

void Game::increaseDifficulty()
{
    double platformVelocity = mParameter.getPlatformVelocity()();
    double platformWidth = mParameter.getPlatformWidth()();
    double ballVelocity = mParameter.getBallVelocity()();
    double ballGravity = mParameter.getBallGravity()();

    platformVelocity += platformVelocityIncrease;
    platformWidth -= platformWidthDecrease;
    ballVelocity += ballVelocityIncrease;
    ballGravity += ballGravityIncrease;

    platformVelocity =
        std::clamp(platformVelocity, platformVelocity, platformVelocityMax);
    platformWidth = std::clamp(platformWidth, platformWidthMin, platformWidth);
    ballVelocity = std::clamp(ballVelocity, ballVelocity, ballVelocityMax);
    ballGravity = std::clamp(ballGravity, ballGravity, ballGravityMax);

    mParameter.setPlatformVelocity(Velocity{platformVelocity});
    mParameter.setPlatformWidth(Width{platformWidth});
    mParameter.setBallVelocity(Velocity{ballVelocity});
    mParameter.setBallGravity(Gravity{ballGravity});
}

Level Game::loadLevel(int levelIDX)
{
    assert(!mLevelFilenames.empty());

    auto level = readFromFile(mLevelFilenames.at(levelIDX - 1));
    level.setParameter(mParameter);
    return level;
}

void Game::updateValuesInTitleBar()
{
    mRenderer.setWindowTitle(
        makeTitle(mCurrentLevelIDX, mLifes, mScore, mHighscore));
}

bool Game::ballLost()
{
    return mLevel.ball.bottomRight().y >= mLevel.gridHeight();
}

void Game::handleBallCollisions()
{
    if (reflect(mLevel.ball, mLevel.leftWall())) {
        return;
    }
    if (reflect(mLevel.ball, mLevel.rightWall())) {
        return;
    }
    if (reflect(mLevel.ball, mLevel.topWall())) {
        return;
    }
    if (reflect(mLevel.ball, mLevel.platform)) {
        playHitPlatform(mAudioDevice);
        return;
    }
    for (auto& indestructibleBrick : mLevel.indestructibleBricks) {
        if (reflect(mLevel.ball, indestructibleBrick)) {
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
                playDestroyBrick(mAudioDevice);
                mScore += getBrickValue(brick);
                awardExtraLifeIfThresholdReached();
                updateValuesInTitleBar();
            }
            else {
                playHitBrick(mAudioDevice);
            }
            return;
        }
    }
}

long long Game::getBrickValue(const Brick& brick) const
{
    return pointsPerBrickHitpoints * brick.startHitpoints() * mCurrentLevelIDX;
}

void Game::awardExtraLifeIfThresholdReached()
{
    auto extraLifeDivisor = static_cast<long long>(mScore / pointsForExtraLife);
    if (extraLifeDivisor != mLastExtraLifeDivisor) {
        playExtraLife(mAudioDevice);
        ++mLifes;
        mLastExtraLifeDivisor = extraLifeDivisor;
    }
}

long long loadHighscore()
{
    std::ifstream ifs{highscoreFilename};
    if (!ifs.is_open()) {
        return 0;
    }
    std::string s;
    ifs >> s;
    if (!isNumber<long long>(s)) {
        return 0;
    }
    return std::stoll(s);
}

void writeHighscore(long long highscore)
{
    std::ofstream ofs{highscoreFilename};
    if (!ofs) {
        throw std::runtime_error("void writeHighscore(long long highscore)\n"
                                 "File could not be opened\n");
    }
    ofs << highscore;
}

std::string makeTitle(int level, int lifes, long long score,
                      long long highscore)
{
    return std::string{"Level: " + std::to_string(level) +
                       "     "
                       "Lifes: " +
                       std::to_string(lifes) +
                       "     "
                       "Score: " +
                       std::to_string(score) +
                       "     "
                       "Highscore: " +
                       std::to_string(highscore)};
}

bool allBricksAreDestroyed(const std::vector<Brick> bricks)
{
    return std::find_if(bricks.begin(), bricks.end(), [](const Brick& b) {
               return !b.isDestroyed();
           }) == bricks.end();
}

void delayToFramerate(double elapsedTimeInMS)
{
    if (elapsedTimeInMS < msPerFrame) {
        wait(std::chrono::milliseconds{
            static_cast<int>(msPerFrame - elapsedTimeInMS)});
    }
}

std::vector<std::string>
getLevelFilenamesFromFolder(const std::string& folderName)
{
    std::vector<std::string> names;
    for (auto& p : std::filesystem::directory_iterator(folderName)) {
        if (p.path().extension() == ".lvl") {
            names.emplace_back(std::filesystem::absolute(p.path()));
        }
    }
    std::sort(names.begin(), names.end());
    return names;
}
} // namespace bricks