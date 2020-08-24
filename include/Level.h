#ifndef LEVEL_H
#define LEVEL_H

#include "game_objects/Ball.h"
#include "game_objects/Brick.h"
#include "game_objects/IndestructibleBrick.h"
#include "game_objects/Platform.h"
#include "game_objects/Wall.h"

#include "DifficultyParameter.h"

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
    Level() = default;
    Level(const DifficultyParameter& parameter,
          const types::GridWidth& gridWidth,
          const types::GridHeight& gridHeight,
          const std::vector<game_objects::Brick>& bricks_,
          const std::vector<game_objects::IndestructibleBrick>&
              indestructibleBricks_);

    int gridWidth() const;
    int gridHeight() const;

    game_objects::Wall leftWall() const;
    game_objects::Wall rightWall() const;
    game_objects::Wall topWall() const;

    void setParameter(const DifficultyParameter& parameter);
    void resetBall();
    void resetPlatform();

private:
    game_objects::Wall makeLeftWall() const;
    game_objects::Wall makeRightWall() const;
    game_objects::Wall makeTopWall() const;
    game_objects::Platform makePlatform(const types::Width& width,
                                        const types::Velocity& velocity) const;
    game_objects::Ball makeBall(const types::Velocity& velocity,
                                const types::Gravity& gravity) const;

    static void transposeCoordinatesWithWalls(game_objects::GameObject& obj);

    DifficultyParameter mParameter;
    int mGridWidth{0};
    int mGridHeight{0};
    game_objects::Wall mLeftWall;
    game_objects::Wall mRightWall;
    game_objects::Wall mTopWall;

public:
    game_objects::Platform platform;
    game_objects::Ball ball;

    std::vector<game_objects::Brick> bricks;
    std::vector<game_objects::IndestructibleBrick> indestructibleBricks;
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