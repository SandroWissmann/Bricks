#ifndef GAME_OBJECTS_IMPROVED_PHYSICS_H
#define GAME_OBJECTS_IMPROVED_PHYSICS_H

#include <memory>
#include <optional>
#include <vector>

namespace bricks::types {
class Angle;
}

namespace bricks::game_objects {

class Ball;
class GameObject;
class Platform;
class Brick;
class IndestructibleBrick;
class Wall;
} // namespace bricks::game_objects

namespace bricks::game_objects::improved {

bool reflectFromPlatform(const Ball& ball, const Platform& platform);

std::vector<std::shared_ptr<GameObject>> reflectFromGameObjects(
    const Ball& ball, const std::vector<Wall>& walls,
    const std::vector<IndestructibleBrick>& indestructibleBrick,
    std::vector<Brick>& bricks);

types::Angle clampAngle(const types::Angle& angle);

bool isSmaller(double angle, double targetAngle, double delta);

bool isBigger(double angle, double targetAngle, double delta);

double calcAngleFactor(double xBall, double xLeft, double xCenter,
                       double xRight);

} // namespace bricks::game_objects::improved

#endif