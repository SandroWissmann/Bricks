#include "Game.h"

#include "game_objects/Physics.h"

#include "utility/IsNumber.h"
#include "utility/TimeMeasure.h"

#include "Level.h"
#include "Renderer.h"

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

constexpr std::size_t framesPerSecond{60};
constexpr std::size_t msPerFrame{1000 / framesPerSecond};

constexpr int pointsPerBrickHitpoints{100};
constexpr int pointsForExtraLife{10000};

constexpr auto highscoreFilename = "highscore.dat";

Game::Game(std::size_t screenWidth, std::size_t screenHeight)
    : mLevelFilenames{getLevelFilenamesFromFolder("level")},
      mLevel{loadLevel(1)}, mRenderer{Renderer{
                                screenWidth, screenHeight,
                                static_cast<std::size_t>(mLevel.gridWidth()),
                                static_cast<std::size_t>(mLevel.gridHeight())}},
      mAudioDevice{}, mHighscore{loadHighscore()}
{
    updateValuesInTitleBar();
}

void Game::run()
{
    while (true) {
        runLevel();
        if (mQuit) {
            return;
        }
        if (mGameOver) {
            playGameOver(mAudioDevice);
            if (mScore > mHighscore) {
                mHighscore = mScore;
                writeHighscore(mHighscore);
            }
            mCurrentLevel = 1;
            mLifes = mStartLifes;
            mGameOver = false;
            mScore = 0;
        }
        else if (beatGame()) {
            mCurrentLevel = 1;
        }
        else {
            playNextLevel(mAudioDevice);
            ++mCurrentLevel;
        }
        mLevel = loadLevel(mCurrentLevel);
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

        auto event = getEvent();

        handleEvent(event, mLevel.leftWall(), mLevel.rightWall(), mLevel.ball,
                    mLevel.platform);
        if (mQuit) {
            return;
        }
        if (mPause) {
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

void Game::handleEvent(const Event& event, const Wall& leftWall,
                       const Wall& rightWall, Ball& ball, Platform& platform)
{
    switch (event) {
    case Event::quit:
        [[fallthrough]];
    case Event::escape:
        mQuit = true;
        break;
    case Event::space:
        if (mPause) {
            return;
        }
        if (!ball.isActive()) {
            ball.activate();
        }
        break;
    case Event::left:
        if (mPause) {
            return;
        }
        if (interectsWithLeftX(platform, leftWall)) {
            putBeforeIntersectsWithLeftX(platform, leftWall);
        }
        else {
            moveLeft(platform, msPerFrame);
        }
        break;
    case Event::right:
        if (mPause) {
            return;
        }
        if (interectsWithRightX(platform, rightWall)) {
            putBeforeIntersectsWithRightX(platform, rightWall);
        }
        else {
            moveRight(platform, msPerFrame);
        }
        break;
    case Event::p:
        mPause = !mPause;
        if (mPause) {
            mRenderer.setPause();
        }
        else {
            mRenderer.resetPause();
        }
        break;
    }
}

bool Game::beatGame()
{
    return mCurrentLevel >= mLevelFilenames.size();
}

Level Game::loadLevel(int level)
{
    assert(!mLevelFilenames.empty());

    return readFromFile(mLevelFilenames.at(level - 1));
}

void Game::updateValuesInTitleBar()
{
    mRenderer.setWindowTitle(
        makeTitle(mCurrentLevel, mLifes, mScore, mHighscore));
}

bool Game::ballLost()
{
    return mLevel.ball.bottomRight().y >= mLevel.gridHeight();
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
    return pointsPerBrickHitpoints * brick.startHitpoints() * mCurrentLevel;
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