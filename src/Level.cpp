#include "Level.h"

#include "types/GridHeight.h"
#include "types/GridWidth.h"
#include "types/Hitpoints.h"
#include "types/Width.h"
#include "types/Point.h"
#include "types/Height.h"

#include "OperatorDegree.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

namespace bricks {

using Point = types::Point;
using Width = types::Width;
using Height = types::Height;
using Velocity = types::Velocity;
using Angle = types::Angle;
using Gravity = types::Gravity;
using Hitpoints = types::Hitpoints;
using GridWidth = types::GridWidth;
using GridHeight = types::GridHeight;

static constexpr auto wallThickness{1.0};

static constexpr auto platformWidth{4.0};
static constexpr auto platformHeight{0.5};
static constexpr auto platformVelocity{18.0};

static constexpr auto ballWidth{0.75};
static constexpr auto ballHeight{0.75};
static constexpr auto ballVelocity{16.0};
static constexpr auto ballAngle{135.0_deg};
static constexpr auto ballGravity{1.5};

Level::Level()
    : mGridWidth{}, mGridHeight{}, mLeftWall{}, mRightWall{}, mTopWall{},
      platform{}, ball{}, bricks{}, indestructibleBricks{}
{
}

Level::Level(const GridWidth& gridWidth, const GridHeight& gridHeight,
             const std::vector<Brick>& bricks_,
             const std::vector<IndestructibleBrick>& indestructibleBricks_)
    : mGridWidth{gridWidth()}, 
    mGridHeight{gridHeight()},
      mLeftWall{makeLeftWall()}, mRightWall{makeRightWall()},
      mTopWall{makeTopWall()}, platform{makePlatform()}, ball{makeBall()},
      bricks{bricks_}, indestructibleBricks{indestructibleBricks_}
{
    assert(mGridWidth > 0);
    assert(mGridHeight > 0);

    mGridWidth += 2*wallThickness;
    mGridHeight += wallThickness;

    transposeCoordinatesWithWalls(platform);
    transposeCoordinatesWithWalls(ball);
    for(auto& brick : bricks) {
        transposeCoordinatesWithWalls(brick);
    }
    for(auto& indestructibleBrick : indestructibleBricks) {
        transposeCoordinatesWithWalls(indestructibleBrick);
    }
}

int Level::gridWidth() const
{
    return mGridWidth;
}

int Level::gridHeight() const
{
    return mGridHeight;
}

Wall Level::leftWall() const
{
    return mLeftWall;
}

Wall Level::rightWall() const
{
    return mRightWall;
}

Wall Level::topWall() const
{
    return mTopWall;
}

void Level::resetBall()
{
    ball = makeBall();
}
void Level::resetPlatform()
{
    platform = makePlatform();
}

Wall Level::makeLeftWall()
{
    return Wall{Point{0, 0}, 
        Width{wallThickness},
        Height{static_cast<double>(mGridHeight + wallThickness)}};
}

Wall Level::makeRightWall()
{
    return Wall{Point{mGridWidth + wallThickness, 0.0}, 
                Width{wallThickness},
                Height{static_cast<double>(mGridHeight + wallThickness)}};
}

Wall Level::makeTopWall()
{
    return Wall{Point{wallThickness, 0},
                Width{static_cast<double>(mGridWidth)}, 
                Height{wallThickness}};
}
Platform Level::makePlatform()
{
    auto p = impl::platformInitPosition(platformWidth, mGridWidth, mGridHeight);

    return Platform{p,
                    Width{platformWidth},
                    Height{platformHeight},
                    Velocity{platformVelocity}};
}

Ball Level::makeBall()
{
    auto p = impl::ballInitPosition(mGridWidth, mGridHeight);

    return Ball{p,
                Width{ballWidth},
                Height{ballHeight},
                Velocity{ballVelocity},
                Angle{ballAngle},
                Gravity{ballGravity}};
}

void Level::transposeCoordinatesWithWalls(GameObject& obj)
{
    auto p = obj.topLeft();
    p.x += wallThickness;
    p.y += wallThickness;
    obj.setTopLeft(p);
}

Level readFromFile(const std::string& filename)
{
    std::ifstream ifs{filename};
    if (!ifs.is_open()) {
        throw std::runtime_error("File:" + filename + "could not be opend\n");
    }
    Level level;
    ifs >> level;
    if (!ifs) {
        std::runtime_error("Could not read level from file: " + filename +
                           "\n");
    }
    return level;
}

std::istream& operator>>(std::istream& is, Level& obj)
{
    std::string line;
    std::getline(is, line);
    std::istringstream ist{line};

    GridWidth gridWidth;
    ist >> gridWidth;
    if (!ist) {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    GridHeight gridHeight;
    ist >> gridHeight;
    if (!ist) {
        is.setstate(std::ios_base::failbit);
        return is;
    }

    std::vector<Brick> bricks;
    std::vector<IndestructibleBrick> indestructibleBricks;

    while (std::getline(is, line)) {

        if (impl::isComment(line)) {
            continue;
        }

        std::istringstream ist{line};

        Point point;
        ist >> point;
        if (!ist) {
            is.setstate(std::ios_base::failbit);
            return is;
        }
        if (point.x > gridWidth()) {
            is.setstate(std::ios_base::failbit);
            return is;
        }
        if (point.y > gridHeight()) {
            is.setstate(std::ios_base::failbit);
            return is;
        }

        Width length;
        ist >> length;
        if (!ist) {
            is.setstate(std::ios_base::failbit);
            return is;
        }

        Height height;
        ist >> height;
        if (!ist) {
            is.setstate(std::ios_base::failbit);
            return is;
        }

        Hitpoints hitpoints;
        ist >> hitpoints;
        if (!ist) {
            indestructibleBricks.emplace_back(
                IndestructibleBrick{point, length, height});
        }
        else {
            bricks.emplace_back(Brick{point, length, height, hitpoints});
        }
    }

    obj = std::move(Level{gridWidth, gridHeight, bricks, indestructibleBricks});
    return is;
}

namespace impl {

bool isComment(const std::string line)
{
    std::istringstream ist{line};

    char c;
    ist >> c;
    if (c == '#') {
        return true;
    }
    return false;
}

Point platformInitPosition(double platformWidth, double gridWidth,
                           double gridHeight)
{
    return Point{gridWidth / 2.0 - platformWidth / 2.0, gridHeight - 1.0};
}
Point ballInitPosition(double gridWidth, double gridHeight)
{
    return Point{gridWidth / 2.0, gridHeight - 2.0};
}

} // namespace impl

} // namespace bricks