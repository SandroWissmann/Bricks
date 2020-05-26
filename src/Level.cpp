#include "Level.h"

#include "types/Hitpoints.h"
#include "types/Length.h"
#include "types/Point.h"
#include "types/Width.h"
#include "types/GridWidth.h"
#include "types/GridHeight.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

namespace bricks {

using Point = types::Point;
using Length = types::Length;
using Width = types::Width;
using Hitpoints = types::Hitpoints;
using GridWidth = types::GridWidth;
using GridHeight = types::GridHeight;

    Level::Level(const GridWidth& gridWidth, const GridHeight& gridHeight,
    const std::vector<Brick>& bricks_, 
    const std::vector<IndestructibleBrick>& indestructibleBricks_)
        :mGridWidth{gridWidth()}, mGridHeight{gridHeight()}, bricks{bricks_},
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

} // namespace impl

} // namespace bricks