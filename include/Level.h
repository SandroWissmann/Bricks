#ifndef LEVEL_H
#define LEVEL_H

#include "Ball.h"
#include "Platform.h"
#include "Wall.h"
#include "Brick.h"
#include "IndestructibleBrick.h"

#include <iosfwd>
#include <vector>

namespace bricks {

namespace types{
    class GridWidth;
    class GridHeight;
}

class Level {
public:
    Level();
    Level(const types::GridWidth& gridWidth, const types::GridHeight& gridHeight,
    const std::vector<Brick>& bricks_, 
    const std::vector<IndestructibleBrick>& indestructibleBricks_);

    int gridWidth() const;
    int gridHeight() const;
private:
    int mGridWidth{0};
    int mGridHeight{0};
    Wall leftWall;
    Wall rightWall;
    Wall topWall;

public:
    /*Platform platform;
    Ball ball; */

    std::vector<Brick> bricks;
    std::vector<IndestructibleBrick> indestructibleBricks;
};

Level readFromFile(const std::string &filename);

std::istream &operator>>(std::istream &is, Level &obj);

namespace impl {
bool isComment(const std::string line);
}
} // namespace bricks

#endif // LEVEL_H