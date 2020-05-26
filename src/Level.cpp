#include "Level.h"

#include "types/Hitpoints.h"
#include "types/Length.h"
#include "types/Point.h"
#include "types/Width.h"
#include "types/GridWidth.h"
#include "types/GridHeight.h"

#include "OperatorDegree.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

namespace bricks {

using Point = types::Point;
using Length = types::Length;
using Width = types::Width;
using MaxPositionX = types::MaxPositionX;
using MaxPositionY = types::MaxPositionY;
using Velocity = types::Velocity;
using Angle = types::Angle;
using Gravity = types::Gravity;
using Hitpoints = types::Hitpoints;
using GridWidth = types::GridWidth;
using GridHeight = types::GridHeight;

static constexpr auto wallThickness{ 1.0 };

static constexpr auto platformWidth{ 4.0 };
static constexpr auto platformHeight{0.5};
static constexpr auto platformVelocity{18.0};

static constexpr auto ballWidth{ 0.75 };
static constexpr auto ballHeight{0.75};
static constexpr auto ballVelocity{16.0};
static constexpr auto ballAngle{135.0_deg};
static constexpr auto ballGravity{1.5};

    Level::Level()
    :mGridWidth{},
    mGridHeight{},
    leftWall{},
    rightWall{},
    topWall{},
    platform{}, 
    ball{}, 
    bricks{}, 
    indestructibleBricks{}
    {
    }

    Level::Level(
        const GridWidth& gridWidth, 
    const GridHeight& gridHeight,
    const std::vector<Brick>& bricks_, 
    const std::vector<IndestructibleBrick>& indestructibleBricks_)
        :mGridWidth{gridWidth()}, 
        mGridHeight{gridHeight()}, 
        leftWall{},
        rightWall{},
        topWall{},
        platform{},
        ball{}, 
        bricks{bricks_},
        indestructibleBricks{indestructibleBricks_}
    {
        assert(mGridWidth > 0);
        assert(mGridHeight > 0);
    }

int Level::gridWidth() const
{
    return mGridWidth;
}

int Level::gridHeight() const
{
    return mGridHeight;
}

Wall Level::makeLeftWall()
{
    return Wall{
        Point{0.0, 0.0},
        Length{wallThickness}, 
        Width{static_cast<double>(mGridHeight)}
    };
}

Wall Level::makeRightWall()
{
    return Wall{
        Point{mGridWidth - wallThickness, 0.0},
        Length{wallThickness}, 
        Width{static_cast<double>(mGridHeight)}
    };
}

Wall Level::makeTopWall()
{
    return Wall{
        Point{wallThickness, 0.0},
        Length{mGridWidth - 2.0 * wallThickness}, 
        Width{wallThickness}
    };
}
Platform Level::makePlatform()
{
    auto p = impl::platformInitPosition(platformWidth, mGridWidth, mGridHeight);

    return Platform{
        p,
        Length{platformWidth},  
        Width{platformHeight}, 
        MaxPositionX{static_cast<double>(mGridWidth)},
        MaxPositionY{static_cast<double>(mGridHeight)},
        Velocity{platformVelocity}
        };
}

Ball Level::makeBall()
{
    auto p = impl::ballInitPosition(mGridWidth, mGridHeight);

    return Ball{
        p,
        Length{ballWidth},
        Width{ballHeight},
        MaxPositionX{static_cast<double>(mGridWidth)},
        MaxPositionY{static_cast<double>(mGridHeight)},  
        Velocity{ballVelocity},
        Angle{ballAngle},
        Gravity{ballGravity}                     
    };
}

Level readFromFile(const std::string &filename)
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

std::istream &operator>>(std::istream &is, Level &obj)
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
        if(point.x > gridWidth()) {
            is.setstate(std::ios_base::failbit);
            return is;        
        }
        if(point.y > gridHeight()) {
            is.setstate(std::ios_base::failbit);
            return is;        
        }

        Length length;
        ist >> length;
        if (!ist) {
            is.setstate(std::ios_base::failbit);
            return is;
        }

        Width width;
        ist >> width;
        if (!ist) {
            is.setstate(std::ios_base::failbit);
            return is;
        }

        Hitpoints hitpoints;
        ist >> hitpoints;
        if (!ist) {
            indestructibleBricks.emplace_back(
                IndestructibleBrick{point, length, width});
        }
        else {
            bricks.emplace_back(Brick{point, length, width, hitpoints});
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

Point platformInitPosition(
    double platformWidth, double gridWidth, double gridHeight)
{
    return Point{
        gridWidth / 2.0 - platformWidth / 2.0,
        gridHeight - 1.0
    };
}
Point ballInitPosition(
    double gridWidth, double gridHeight)
{
    return Point{
        gridWidth / 2.0,
        gridHeight - 2.0
    };    
}

} // namespace impl

} // namespace bricks