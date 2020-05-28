#ifndef LEVEL_H
#define LEVEL_H

#include "Ball.h"
#include "Brick.h"
#include "IndestructibleBrick.h"
#include "Platform.h"
#include "Wall.h"

#include <iosfwd>
#include <vector>

namespace bricks {

namespace types {
class GridWidth;
class GridHeight;
struct Point;
} // namespace types

class Level {
public:
    Level();
    Level(const types::GridWidth& gridWidth,
          const types::GridHeight& gridHeight,
          const std::vector<Brick>& bricks_,
          const std::vector<IndestructibleBrick>& indestructibleBricks_);

    int gridWidth() const;
    int gridHeight() const;

    Wall leftWall() const;
    Wall rightWall() const;
    Wall topWall() const;

    void resetBall();
    void resetPlatform();

private:
    Wall makeLeftWall();
    Wall makeRightWall();
    Wall makeTopWall();
    Platform makePlatform();
    Ball makeBall();

    int mGridWidth{0};
    int mGridHeight{0};
    Wall mLeftWall;
    Wall mRightWall;
    Wall mTopWall;

public:
    Platform platform;
    Ball ball;

    std::vector<Brick> bricks;
    std::vector<IndestructibleBrick> indestructibleBricks;
};

Level readFromFile(const std::string& filename);

std::istream& operator>>(std::istream& is, Level& obj);

namespace impl {
bool isComment(const std::string line);

types::Point platformInitPosition(double platformWidth, double gridWidth,
                                  double gridHeight);
types::Point ballInitPosition(double gridWidth, double gridHeight);
} // namespace impl
} // namespace bricks

#endif // LEVEL_H