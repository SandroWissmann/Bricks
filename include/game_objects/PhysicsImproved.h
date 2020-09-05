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

enum class Intersection {
    none,
    left,
    topLeft,
    top,
    topRight,
    right,
    bottomRight,
    bottom,
    bottomLeft
};

struct ObjectIntersectionPair {
    std::shared_ptr<GameObject> object;
    Intersection intersection;
};

bool reflectFromPlatform(const Ball& ball, const Platform& platform);

std::vector<std::shared_ptr<GameObject>> reflectFromGameObjects(
    const Ball& ball, const std::vector<Wall>& walls,
    const std::vector<IndestructibleBrick>& indestructibleBrick,
    std::vector<Brick>& bricks);

bool reflectFromSingleObject(const Ball& ball, const Platform& platform,
                             const Intersection& intersection);

bool reflectFromSingleObject(const Ball& ball, const GameObject& obj,
                             const Intersection& intersection);

void reflectFromMultipleObjects(
    Ball& ball,
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs);

bool reflectFromTwoObjectsInCorner(
    Ball& ball,
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs);

bool reflectFromThreeObjectsInCorner(
    Ball& ball,
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs);

bool intersectsInTopLeftCornerWithTwoObjects(
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs);
bool intersectsInTopLeftCornerWithThreeObjects(
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs);
void putBeforeIntersectsWithTopLeftCorner(
    Ball& ball,
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs);

bool intersectsInTopRightCornerWithTwoObjects(
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs);
bool intersectsInTopRightCornerWithThreeObjects(
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs);
void putBeforeIntersectsWithTopRightCorner(
    Ball& ball,
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs);

bool intersectsInBottomRightCornerWithTwoObjects(
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs);
bool intersectsInBottomRightCornerWithThreeObjects(
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs);
void putBeforeIntersectsWithBottomRightCorner(
    Ball& ball,
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs);

bool intersectsInBottomLeftCornerWithTwoObjects(
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs);
bool intersectsInBottomLeftCornerWithThreeObjects(
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs);
void putBeforeIntersectsWithBottomLeftCorner(
    Ball& ball,
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs);

bool intersectsFromLeftWithMultiObjects(
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs);
bool intersectsFromTopWithMultiObjects(
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs);
bool intersectsFromRightWithMultiObjects(
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs);
bool intersectsFromBottomWithMultiObjects(
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs);

bool objectIntersectionPairsContainOnlyValuesFromIntersectionList(
    const std::vector<Intersection>& intersections,
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs);

void reflectFromCollisionWithLeft(Ball& ball, const GameObject& obj);
void reflectFromCollisionWithTop(Ball& ball, const GameObject& obj);

void reflectFromCollisionWithTopRelativeToPositon(Ball& ball,
                                                  const Platform& platform);

void reflectHorizontalItoIV(Ball& ball, const Platform& platform);
void reflectHorizontalIItoIII(Ball& ball, const Platform& platform);

double calcAngleFactor(double xBall, double xLeft, double xCenter,
                       double xRight);

void reflectFromCollisionWithRight(Ball& ball, const GameObject& obj);
void reflectFromCollisionWithBottom(Ball& ball, const GameObject& obj);

bool intersectionIsMoreLeftThanTop(const Ball& ball, const GameObject& obj);
bool intersectionIsMoreTopThanRight(const Ball& ball, const GameObject& obj);
bool intersectionIsMoreRightThanBottom(const Ball& ball, const GameObject& obj);
bool intersectionIsMoreBottomThanLeft(const Ball& ball, const GameObject& obj);

void reflectHorizontal(Ball& ball);
void reflectVertical(Ball& ball);

void putBeforeIntersectsWithRightX(GameObject& a, const GameObject& b);
void putBeforeIntersectsWithLeftX(GameObject& a, const GameObject& b);
void putBeforeIntersectsWithBottomY(Ball& ball, const GameObject& obj);
void putBeforeIntersectsWithTopY(Ball& ball, const GameObject& obj);

types::Angle clampAngle(const types::Angle& angle);

bool isSmaller(double angle, double targetAngle, double delta);

bool isBigger(double angle, double targetAngle, double delta);

long double random(long double min, long double max);

} // namespace bricks::game_objects::improved

#endif