#include "Physics.h"

#include "Ball.h"
#include "Brick.h"
#include "GameObject.h"
#include "IndestructibleBrick.h"
#include "Platform.h"
#include "Wall.h"

#include "../types/Angle.h"
#include "../types/Point.h"
#include "../utility/NearlyEqual.h"
#include "../utility/OperatorDegree.h"

#include <algorithm>
#include <random>

#include <cassert>

namespace bricks::game_objects {

using namespace utility;

using Angle = types::Angle;
using Point = types::Point;
using Quadrant = types::Quadrant;

template <typename GameObjectType>
std::vector<ObjectIntersectionPair>
getObjectIntersectionPairs(const Ball& ball,
                           const std::vector<GameObjectType>& gameObjects)
{
    std::vector<ObjectIntersectionPair> objectIntersectionPairs;

    for (const auto& gameObject : gameObjects) {
        auto intersection = getIntersection(ball, gameObject);

        if (intersection == Intersection::none) {
            continue;
        }
        auto uniqueGameObject = std::make_unique<GameObjectType>(gameObject);

        objectIntersectionPairs.push_back(
            ObjectIntersectionPair{std::move(uniqueGameObject), intersection});
    }
    return objectIntersectionPairs;
}

template std::vector<ObjectIntersectionPair>
getObjectIntersectionPairs<IndestructibleBrick>(
    const Ball& ball, const std::vector<IndestructibleBrick>& gameObjects);

template std::vector<ObjectIntersectionPair>
getObjectIntersectionPairs<Wall>(const Ball& ball,
                                 const std::vector<Wall>& gameObjects);

bool reflectFromPlatform(Ball& ball, const Platform& platform)
{
    auto intersection = getIntersection(ball, platform);
    if (intersection == Intersection::none) {
        return false;
    }
    reflectFromSinglePlatform(ball, platform, intersection);
    auto angle = clampAngle(ball.angle());
    ball.setAngle(angle);
    return false;
}

std::vector<std::shared_ptr<GameObject>> reflectFromGameObjects(
    Ball& ball, const std::vector<Wall>& walls,
    const std::vector<IndestructibleBrick>& indestructibleBricks,
    std::vector<Brick>& bricks)
{
    auto wallPairs = getObjectIntersectionPairs(ball, walls);

    auto indBrickPairs = getObjectIntersectionPairs(ball, indestructibleBricks);

    auto brickPairs = getObjectIntersectionPairs(ball, bricks);

    std::vector<ObjectIntersectionPair> objectIntersectionPairs;
    objectIntersectionPairs.reserve(wallPairs.size() + indBrickPairs.size() +
                                    brickPairs.size());

    std::move(wallPairs.begin(), wallPairs.end(),
              std::back_inserter(objectIntersectionPairs));
    std::move(indBrickPairs.begin(), indBrickPairs.end(),
              std::back_inserter(objectIntersectionPairs));
    std::move(brickPairs.begin(), brickPairs.end(),
              std::back_inserter(objectIntersectionPairs));

    if (objectIntersectionPairs.size() == 1) {
        reflectFromSingleObject(ball, *objectIntersectionPairs[0].object.get(),
                                objectIntersectionPairs[0].intersection);
        auto angle = clampAngle(ball.angle());
        ball.setAngle(angle);
        return std::vector<std::shared_ptr<GameObject>>{
            std::move(objectIntersectionPairs[0].object)};
    }
    if (objectIntersectionPairs.size() > 1) {
        reflectFromMultipleObjects(ball, objectIntersectionPairs);
        auto angle = clampAngle(ball.angle());
        ball.setAngle(angle);

        std::vector<std::shared_ptr<GameObject>> hitObjects;
        for (auto& objectIntersectionPair : objectIntersectionPairs) {
            hitObjects.push_back(std::move(objectIntersectionPair.object));
        }
        return hitObjects;
    }
    return std::vector<std::shared_ptr<GameObject>>{};
}

std::vector<ObjectIntersectionPair>
getObjectIntersectionPairs(const Ball& ball, std::vector<Brick>& bricks)
{
    std::vector<ObjectIntersectionPair> objectIntersectionPairs;

    for (auto& brick : bricks) {
        if (brick.isDestroyed()) {
            continue;
        }

        auto intersection = getIntersection(ball, brick);

        if (intersection == Intersection::none) {
            continue;
        }
        brick.decreaseHitpoints();
        auto uniqueGameObject = std::make_unique<Brick>(brick);

        objectIntersectionPairs.push_back(
            ObjectIntersectionPair{std::move(uniqueGameObject), intersection});
    }
    return objectIntersectionPairs;
}

Intersection getIntersection(const Ball& ball, const GameObject& obj)
{
    std::vector<Intersection> intersections{};

    if (topLeftIntersectsWithBottomRight(ball.topLeft(), obj.bottomRight(),
                                         obj.topLeft())) {
        intersections.push_back(Intersection::bottomRight);
    }
    if (topRightIntersectsWithBottomLeft(ball.topRight(), obj.bottomLeft(),
                                         obj.topRight())) {
        intersections.push_back(Intersection::bottomLeft);
    }
    if (bottomLeftIntersectsWithTopRight(ball.bottomLeft(), obj.topRight(),
                                         obj.bottomLeft())) {
        intersections.push_back(Intersection::topRight);
    }
    if (bottomRightIntersectsWithTopLeft(ball.bottomRight(), obj.topLeft(),
                                         obj.bottomRight())) {
        intersections.push_back(Intersection::topLeft);
    }

    if (intersections.empty()) {
        return Intersection::none;
    }
    if (intersections.size() == 1) {
        return intersections[0];
    }
    if (intersections.size() == 2) {
        if (intersectsLeft(intersections)) {
            return Intersection::left;
        }
        if (intersectsTop(intersections)) {
            return Intersection::top;
        }
        if (intersectsRight(intersections)) {
            return Intersection::right;
        }
        if (intersectsBottom(intersections)) {
            return Intersection::bottom;
        }
    }
    return Intersection::none;
}

bool bottomRightIntersectsWithTopLeft(const Point& bottomRight1,
                                      const Point& topLeft2,
                                      const Point& bottomRight2)
{
    auto xIsInside =
        topLeft2.x <= bottomRight1.x && bottomRight1.x < bottomRight2.x;
    auto yIsInside =
        topLeft2.y <= bottomRight1.y && bottomRight1.y < bottomRight2.y;
    return xIsInside and yIsInside;
}

bool bottomLeftIntersectsWithTopRight(const Point& bottomLeft1,
                                      const Point& topRight2,
                                      const Point& bottomLeft2)
{
    auto xIsInside =
        topRight2.x >= bottomLeft1.x && bottomLeft1.x > bottomLeft2.x;
    auto yIsInside =
        topRight2.y <= bottomLeft1.y && bottomLeft1.y < bottomLeft2.y;
    return xIsInside and yIsInside;
}

bool topLeftIntersectsWithBottomRight(const Point& topLeft1,
                                      const Point& bottomRight2,
                                      const Point& topLeft2)
{
    auto xIsInside = bottomRight2.x >= topLeft1.x && topLeft1.x > topLeft2.x;
    auto yIsInside = bottomRight2.y >= topLeft1.y && topLeft1.y > topLeft2.y;
    return xIsInside and yIsInside;
}

bool topRightIntersectsWithBottomLeft(const Point& topRight1,
                                      const Point& bottomLeft2,
                                      const Point& topRight2)
{
    auto xIsInside = bottomLeft2.x <= topRight1.x && topRight1.x < topRight2.x;
    auto yIsInside = bottomLeft2.y >= topRight1.y && topRight1.y > topRight2.y;
    return xIsInside and yIsInside;
}

bool intersectsLeft(const std::vector<Intersection>& intersections)
{
    assert(intersections.size() == 2);
    std::vector<Intersection> expectedIntersections{Intersection::bottomLeft,
                                                    Intersection::topLeft};
    return allExpectedIntersectionsAreInIntersections(expectedIntersections,
                                                      intersections);
}

bool intersectsTop(const std::vector<Intersection>& intersections)
{
    assert(intersections.size() == 2);
    std::vector<Intersection> expectedIntersections{Intersection::topLeft,
                                                    Intersection::topRight};
    return allExpectedIntersectionsAreInIntersections(expectedIntersections,
                                                      intersections);
}

bool intersectsRight(const std::vector<Intersection>& intersections)
{
    assert(intersections.size() == 2);
    std::vector<Intersection> expectedIntersections{Intersection::topRight,
                                                    Intersection::bottomRight};
    return allExpectedIntersectionsAreInIntersections(expectedIntersections,
                                                      intersections);
}

bool intersectsBottom(const std::vector<Intersection>& intersections)
{
    assert(intersections.size() == 2);
    std::vector<Intersection> expectedIntersections{Intersection::bottomRight,
                                                    Intersection::bottomLeft};
    return allExpectedIntersectionsAreInIntersections(expectedIntersections,
                                                      intersections);
}

bool allExpectedIntersectionsAreInIntersections(
    const std::vector<Intersection>& expectedIntersections,
    const std::vector<Intersection>& intersections)
{
    for (const auto& expectedIntersection : expectedIntersections) {
        auto it = std::find(intersections.begin(), intersections.end(),
                            expectedIntersection);
        if (it == intersections.end()) {
            return false;
        }
    }
    return true;
}

void reflectFromSinglePlatform(Ball& ball, const Platform& platform,
                               const Intersection& intersection)
{
    switch (intersection) {
    case Intersection::none:
        break;
    case Intersection::topLeft:
        if (intersectionIsMoreLeftThanTop(ball, platform)) {
            reflectFromCollisionWithLeft(ball, platform);
        }
        else {
            reflectFromCollisionWithTopRelativeToPositon(ball, platform);
        }
        break;
    case Intersection::top:
        reflectFromCollisionWithTopRelativeToPositon(ball, platform);
        break;
    case Intersection::topRight:
        if (intersectionIsMoreTopThanRight(ball, platform)) {
            reflectFromCollisionWithTopRelativeToPositon(ball, platform);
        }
        else {
            reflectFromCollisionWithRight(ball, platform);
        }
        break;
    default:
        reflectFromSingleObject(ball, platform, intersection);
    }
}

void reflectFromSingleObject(Ball& ball, const GameObject& obj,
                             const Intersection& intersection)
{
    switch (intersection) {
    case Intersection::none:
        break;
    case Intersection::left:
        reflectFromCollisionWithLeft(ball, obj);
        break;
    case Intersection::topLeft:
        if (intersectionIsMoreLeftThanTop(ball, obj)) {
            reflectFromCollisionWithLeft(ball, obj);
        }
        else {
            reflectFromCollisionWithTop(ball, obj);
        }
        break;
    case Intersection::top:
        reflectFromCollisionWithTop(ball, obj);
        break;
    case Intersection::topRight:
        if (intersectionIsMoreTopThanRight(ball, obj)) {
            reflectFromCollisionWithTop(ball, obj);
        }
        else {
            reflectFromCollisionWithRight(ball, obj);
        }
        break;
    case Intersection::right:
        reflectFromCollisionWithRight(ball, obj);
        break;
    case Intersection::bottomRight:
        if (intersectionIsMoreRightThanBottom(ball, obj)) {
            reflectFromCollisionWithRight(ball, obj);
        }
        else {
            reflectFromCollisionWithBottom(ball, obj);
        }
        break;
    case Intersection::bottom:
        reflectFromCollisionWithBottom(ball, obj);
        break;
    case Intersection::bottomLeft:
        if (intersectionIsMoreBottomThanLeft(ball, obj)) {
            reflectFromCollisionWithBottom(ball, obj);
        }
        else {
            reflectFromCollisionWithLeft(ball, obj);
        }
        break;
    }
}

void reflectFromMultipleObjects(
    Ball& ball,
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs)
{
    assert(objectIntersectionPairs.size() > 1);

    if (intersectsFromLeftWithMultiObjects(objectIntersectionPairs)) {
        reflectFromCollisionWithLeft(ball,
                                     *objectIntersectionPairs[0].object.get());
    }
    else if (intersectsFromTopWithMultiObjects(objectIntersectionPairs)) {
        reflectFromCollisionWithTop(ball,
                                    *objectIntersectionPairs[0].object.get());
    }
    else if (intersectsFromRightWithMultiObjects(objectIntersectionPairs)) {
        reflectFromCollisionWithRight(ball,
                                      *objectIntersectionPairs[0].object.get());
    }
    else if (intersectsFromBottomWithMultiObjects(objectIntersectionPairs)) {
        reflectFromCollisionWithBottom(
            ball, *objectIntersectionPairs[0].object.get());
    }

    if (objectIntersectionPairs.size() == 2) {
        if (reflectFromTwoObjectsInCorner(ball, objectIntersectionPairs)) {
            return;
        }
    }
    if (objectIntersectionPairs.size() == 3) {
        if (reflectFromThreeObjectsInCorner(ball, objectIntersectionPairs)) {
            return;
        }
    }
}

bool reflectFromTwoObjectsInCorner(
    Ball& ball,
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs)
{
    if (intersectsInTopLeftCornerWithTwoObjects(objectIntersectionPairs)) {
        putBeforeIntersectsWithTopLeftCorner(ball, objectIntersectionPairs);
        auto angle = ball.angle();
        angle.set(angle.get() - 180.0_deg);
        ball.setAngle(angle);
        return true;
    }
    if (intersectsInTopRightCornerWithTwoObjects(objectIntersectionPairs)) {
        putBeforeIntersectsWithTopRightCorner(ball, objectIntersectionPairs);
        auto angle = ball.angle();
        angle.set(angle.get() - 180.0_deg);
        ball.setAngle(angle);
        return true;
    }
    if (intersectsInBottomRightCornerWithTwoObjects(objectIntersectionPairs)) {
        putBeforeIntersectsWithBottomRightCorner(ball, objectIntersectionPairs);
        auto angle = ball.angle();
        angle.set(angle.get() + 180.0_deg);
        ball.setAngle(angle);
        return true;
    }
    if (intersectsInBottomLeftCornerWithTwoObjects(objectIntersectionPairs)) {
        putBeforeIntersectsWithBottomLeftCorner(ball, objectIntersectionPairs);
        auto angle = ball.angle();
        angle.set(angle.get() + 180.0_deg);
        ball.setAngle(angle);
        return true;
    }
    return false;
}

bool reflectFromThreeObjectsInCorner(
    Ball& ball,
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs)
{
    if (intersectsInTopLeftCornerWithThreeObjects(objectIntersectionPairs)) {
        putBeforeIntersectsWithTopLeftCorner(ball, objectIntersectionPairs);
        auto angle = ball.angle();
        angle.set(angle.get() - 180.0_deg);
        ball.setAngle(angle);
        return true;
    }
    if (intersectsInTopRightCornerWithThreeObjects(objectIntersectionPairs)) {
        putBeforeIntersectsWithTopRightCorner(ball, objectIntersectionPairs);
        auto angle = ball.angle();
        angle.set(angle.get() - 180.0_deg);
        ball.setAngle(angle);
        return true;
    }
    if (intersectsInBottomRightCornerWithThreeObjects(
            objectIntersectionPairs)) {
        putBeforeIntersectsWithBottomRightCorner(ball, objectIntersectionPairs);
        auto angle = ball.angle();
        angle.set(angle.get() + 180.0_deg);
        ball.setAngle(angle);
        return true;
    }
    if (intersectsInBottomLeftCornerWithThreeObjects(objectIntersectionPairs)) {
        putBeforeIntersectsWithBottomLeftCorner(ball, objectIntersectionPairs);
        auto angle = ball.angle();
        angle.set(angle.get() + 180.0_deg);
        ball.setAngle(angle);
        return true;
    }
    return false;
}

bool intersectsInTopLeftCornerWithTwoObjects(
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs)
{
    std::vector<Intersection> intersectionsVariant1{Intersection::right,
                                                    Intersection::bottomLeft};
    auto isVariant1 = allIntersectionsAreInObjectIntersectionPairs(
        intersectionsVariant1, objectIntersectionPairs);
    if (isVariant1) {
        return true;
    }
    std::vector<Intersection> intersectionsVariant2{Intersection::topRight,
                                                    Intersection::bottom};
    auto isVariant2 = allIntersectionsAreInObjectIntersectionPairs(
        intersectionsVariant2, objectIntersectionPairs);
    return isVariant2;
}

bool intersectsInTopLeftCornerWithThreeObjects(
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs)
{
    assert(objectIntersectionPairs.size() == 3);

    std::vector<Intersection> intersections{Intersection::bottomLeft,
                                            Intersection::bottomRight,
                                            Intersection::topRight};

    return allIntersectionsAreInObjectIntersectionPairs(
        intersections, objectIntersectionPairs);
}

void putBeforeIntersectsWithTopLeftCorner(
    Ball& ball,
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs)
{
    for (const auto& objectIntersectionPair : objectIntersectionPairs) {
        auto intersection = objectIntersectionPair.intersection;
        if (intersection == Intersection::bottomLeft ||
            intersection == Intersection::bottom) {
            putBeforeIntersectsWithTopY(ball,
                                        *objectIntersectionPair.object.get());
        }
        else if (intersection == Intersection::bottomRight) {
            ;
        }
        else if (intersection == Intersection::topRight ||
                 intersection == Intersection::right) {
            putBeforeIntersectsWithLeftX(ball,
                                         *objectIntersectionPair.object.get());
        }
        else {
            assert(true == false);
        }
    }
}

bool intersectsInTopRightCornerWithTwoObjects(
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs)
{
    std::vector<Intersection> intersectionsVariant1{Intersection::bottomRight,
                                                    Intersection::left};
    auto isVariant1 = allIntersectionsAreInObjectIntersectionPairs(
        intersectionsVariant1, objectIntersectionPairs);
    if (isVariant1) {
        return true;
    }
    std::vector<Intersection> intersectionsVariant2{Intersection::bottom,
                                                    Intersection::topLeft};
    auto isVariant2 = allIntersectionsAreInObjectIntersectionPairs(
        intersectionsVariant2, objectIntersectionPairs);
    return isVariant2;
}

bool intersectsInTopRightCornerWithThreeObjects(
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs)
{
    assert(objectIntersectionPairs.size() == 3);

    std::vector<Intersection> intersections{Intersection::bottomRight,
                                            Intersection::bottomLeft,
                                            Intersection::topLeft};

    return allIntersectionsAreInObjectIntersectionPairs(
        intersections, objectIntersectionPairs);
}

void putBeforeIntersectsWithTopRightCorner(
    Ball& ball,
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs)
{
    for (const auto& objectIntersectionPair : objectIntersectionPairs) {
        auto intersection = objectIntersectionPair.intersection;
        if (intersection == Intersection::bottomRight ||
            intersection == Intersection::bottom) {
            putBeforeIntersectsWithTopY(ball,
                                        *objectIntersectionPair.object.get());
        }
        else if (intersection == Intersection::bottomLeft) {
            ;
        }
        else if (intersection == Intersection::topLeft ||
                 intersection == Intersection::left) {
            putBeforeIntersectsWithRightX(ball,
                                          *objectIntersectionPair.object.get());
        }
        else {
            assert(true == false);
        }
    }
}

bool intersectsInBottomRightCornerWithTwoObjects(
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs)
{
    std::vector<Intersection> intersectionsVariant1{Intersection::top,
                                                    Intersection::bottomLeft};
    auto isVariant1 = allIntersectionsAreInObjectIntersectionPairs(
        intersectionsVariant1, objectIntersectionPairs);
    if (isVariant1) {
        return true;
    }
    std::vector<Intersection> intersectionsVariant2{Intersection::left,
                                                    Intersection::topRight};
    auto isVariant2 = allIntersectionsAreInObjectIntersectionPairs(
        intersectionsVariant2, objectIntersectionPairs);
    return isVariant2;
}

bool intersectsInBottomRightCornerWithThreeObjects(
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs)
{
    assert(objectIntersectionPairs.size() == 3);

    std::vector<Intersection> intersections{Intersection::topRight,
                                            Intersection::topLeft,
                                            Intersection::bottomLeft};

    return allIntersectionsAreInObjectIntersectionPairs(
        intersections, objectIntersectionPairs);
}

void putBeforeIntersectsWithBottomRightCorner(
    Ball& ball,
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs)
{
    for (const auto& objectIntersectionPair : objectIntersectionPairs) {
        auto intersection = objectIntersectionPair.intersection;
        if (intersection == Intersection::topRight ||
            intersection == Intersection::top) {
            putBeforeIntersectsWithBottomY(
                ball, *objectIntersectionPair.object.get());
        }
        else if (intersection == Intersection::topLeft) {
            ;
        }
        else if (intersection == Intersection::bottomLeft ||
                 intersection == Intersection::left) {
            putBeforeIntersectsWithRightX(ball,
                                          *objectIntersectionPair.object.get());
        }
        else {
            assert(true == false);
        }
    }
}

bool intersectsInBottomLeftCornerWithTwoObjects(
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs)
{
    std::vector<Intersection> intersectionsVariant1{Intersection::top,
                                                    Intersection::bottomRight};
    auto isVariant1 = allIntersectionsAreInObjectIntersectionPairs(
        intersectionsVariant1, objectIntersectionPairs);
    if (isVariant1) {
        return true;
    }
    std::vector<Intersection> intersectionsVariant2{Intersection::topLeft,
                                                    Intersection::right};
    auto isVariant2 = allIntersectionsAreInObjectIntersectionPairs(
        intersectionsVariant2, objectIntersectionPairs);
    return isVariant2;
}

bool intersectsInBottomLeftCornerWithThreeObjects(
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs)
{
    assert(objectIntersectionPairs.size() == 3);

    std::vector<Intersection> intersections{Intersection::topLeft,
                                            Intersection::topRight,
                                            Intersection::bottomRight};

    return allIntersectionsAreInObjectIntersectionPairs(
        intersections, objectIntersectionPairs);
}

void putBeforeIntersectsWithBottomLeftCorner(
    Ball& ball,
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs)
{
    for (const auto& objectIntersectionPair : objectIntersectionPairs) {
        auto intersection = objectIntersectionPair.intersection;
        if (intersection == Intersection::topLeft ||
            intersection == Intersection::top) {
            putBeforeIntersectsWithBottomY(
                ball, *objectIntersectionPair.object.get());
        }
        else if (intersection == Intersection::topRight) {
            ;
        }
        else if (intersection == Intersection::bottomRight ||
                 intersection == Intersection::right) {
            putBeforeIntersectsWithLeftX(ball,
                                         *objectIntersectionPair.object.get());
        }
        else {
            assert(true == false);
        }
    }
}

bool intersectsFromLeftWithMultiObjects(
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs)
{
    assert(objectIntersectionPairs.size() > 1);

    std::vector<Intersection> intersections{
        Intersection::left, Intersection::topLeft, Intersection::bottomLeft};

    return objectIntersectionPairsContainOnlyValuesFromIntersectionList(
        intersections, objectIntersectionPairs);
}

bool intersectsFromTopWithMultiObjects(
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs)
{
    assert(objectIntersectionPairs.size() > 1);

    std::vector<Intersection> intersections{
        Intersection::top, Intersection::topLeft, Intersection::topRight};

    return objectIntersectionPairsContainOnlyValuesFromIntersectionList(
        intersections, objectIntersectionPairs);
}

bool intersectsFromRightWithMultiObjects(
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs)
{
    assert(objectIntersectionPairs.size() > 1);

    std::vector<Intersection> intersections{
        Intersection::right, Intersection::topRight, Intersection::bottomRight};

    return objectIntersectionPairsContainOnlyValuesFromIntersectionList(
        intersections, objectIntersectionPairs);
}

bool intersectsFromBottomWithMultiObjects(
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs)
{
    assert(objectIntersectionPairs.size() > 1);

    std::vector<Intersection> intersections{Intersection::bottom,
                                            Intersection::bottomRight,
                                            Intersection::bottomLeft};

    return objectIntersectionPairsContainOnlyValuesFromIntersectionList(
        intersections, objectIntersectionPairs);
}

bool objectIntersectionPairsContainOnlyValuesFromIntersectionList(
    const std::vector<Intersection>& intersections,
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs)
{
    for (const auto& objectIntersectionPair : objectIntersectionPairs) {
        auto it = std::find(intersections.begin(), intersections.end(),
                            objectIntersectionPair.intersection);
        if (it == intersections.end()) {
            return false;
        }
    }
    return true;
}

bool allIntersectionsAreInObjectIntersectionPairs(
    const std::vector<Intersection>& intersections,
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs)
{
    for (const auto& intersection : intersections) {
        auto it = std::find_if(
            objectIntersectionPairs.begin(), objectIntersectionPairs.end(),
            [intersection](const ObjectIntersectionPair& obj) {
                return obj.intersection == intersection;
            });
        if (it == objectIntersectionPairs.end()) {
            return false;
        }
    }
    return true;
}

void reflectFromCollisionWithLeft(Ball& ball, const GameObject& obj)
{
    reflectVertical(ball);
    putBeforeIntersectsWithRightX(ball, obj);
}

void reflectFromCollisionWithTop(Ball& ball, const GameObject& obj)
{
    reflectHorizontal(ball);
    putBeforeIntersectsWithBottomY(ball, obj);
}

void reflectFromCollisionWithTopRelativeToPositon(Ball& ball,
                                                  const Platform& platform)
{
    assert(ball.angle().quadrant() != Quadrant::III);
    assert(ball.angle().quadrant() != Quadrant::IV);

    if (ball.angle().quadrant() == Quadrant::I) {
        reflectHorizontalItoIV(ball, platform);
        putBeforeIntersectsWithBottomY(ball, platform);
    }
    else if (ball.angle().quadrant() == Quadrant::II) {
        reflectHorizontalIItoIII(ball, platform);
        putBeforeIntersectsWithBottomY(ball, platform);
    }
}

void reflectHorizontalItoIV(Ball& ball, const Platform& platform)
{
    auto xRight = platform.bottomRight().x;
    auto xLeft = platform.topLeft().x;
    auto xCenter = xRight - (platform.width() / 2.0);
    auto xBall = ball.bottomRight().x;

    auto factor = calcAngleFactor(xBall, xLeft, xCenter, xRight);

    auto newQuadAngle = 60.0_deg - (45.0_deg - 45.0_deg * factor);
    assert(newQuadAngle >= 0.0_deg && newQuadAngle <= 90.0_deg);

    auto angle = ball.angle();
    angle.mirrorHorizontal();
    angle.setQuadrantAngle(newQuadAngle);
    ball.setAngle(angle);
}

void reflectHorizontalIItoIII(Ball& ball, const Platform& platform)
{
    auto xRight = platform.bottomRight().x;
    auto xLeft = platform.topLeft().x;
    auto xCenter = xLeft + (platform.width() / 2.0);
    auto xBall = ball.topLeft().x;

    auto factor = calcAngleFactor(xBall, xLeft, xCenter, xRight);

    auto newQuadAngle = 30.0_deg + (45.0_deg - (45.0_deg * factor));
    assert(newQuadAngle >= 0.0_deg && newQuadAngle <= 90.0_deg);

    auto angle = ball.angle();
    angle.mirrorHorizontal();
    angle.setQuadrantAngle(newQuadAngle);
    ball.setAngle(angle);
}

double calcAngleFactor(double xBall, double xLeft, double xCenter,
                       double xRight)
{
    assert(xLeft < xCenter);
    assert(xCenter < xRight);

    xBall = std::clamp(xBall, xLeft, xRight);

    auto len = xCenter - xLeft;
    double factor = 0.0;
    if (xBall <= xCenter) {
        factor = (xCenter - xBall) / len;
    }
    else {
        factor = (xBall - xCenter) / len;
    }
    factor = std::clamp(factor, 0.0, 1.0);
    assert(factor >= 0.0 && factor <= 1.0);
    return factor;
}

void reflectFromCollisionWithRight(Ball& ball, const GameObject& obj)
{
    reflectVertical(ball);
    putBeforeIntersectsWithLeftX(ball, obj);
}

void reflectFromCollisionWithBottom(Ball& ball, const GameObject& obj)
{
    reflectHorizontal(ball);
    putBeforeIntersectsWithTopY(ball, obj);
}

bool intersectionIsMoreLeftThanTop(const Ball& ball, const GameObject& obj)
{
    auto x = ball.bottomRight().x - obj.topLeft().x;
    auto y = ball.bottomRight().y - obj.topLeft().y;
    assert(x >= 0);
    assert(y >= 0);
    return y > x;
}

bool intersectionIsMoreTopThanRight(const Ball& ball, const GameObject& obj)
{
    auto x = obj.topRight().x - ball.bottomLeft().x;
    auto y = ball.bottomLeft().y - obj.topRight().y;
    assert(x >= 0);
    assert(y >= 0);
    return x > y;
}

bool intersectionIsMoreRightThanBottom(const Ball& ball, const GameObject& obj)
{
    auto x = obj.bottomRight().x - ball.topLeft().x;
    auto y = obj.bottomRight().y - ball.topLeft().y;
    assert(x >= 0);
    assert(y >= 0);
    return y > x;
}

bool intersectionIsMoreBottomThanLeft(const Ball& ball, const GameObject& obj)
{
    auto x = ball.topRight().x - obj.bottomLeft().x;
    auto y = obj.bottomLeft().y - ball.topRight().y;
    assert(x >= 0);
    assert(y >= 0);
    return x > y;
}

void reflectHorizontal(Ball& ball)
{
    auto angle = ball.angle();
    angle.mirrorHorizontal();
    ball.setAngle(angle);
}

void reflectVertical(Ball& ball)
{
    auto angle = ball.angle();
    angle.mirrorVertical();
    ball.setAngle(angle);
}

void putBeforeIntersectsWithRightX(GameObject& a, const GameObject& b)
{
    Point p = a.topLeft();
    p.x = b.topLeft().x - a.width();
    a.setTopLeft(p);
}

void putBeforeIntersectsWithLeftX(GameObject& a, const GameObject& b)
{
    Point p = a.topLeft();
    p.x = b.bottomRight().x;
    a.setTopLeft(p);
}

void putBeforeIntersectsWithBottomY(Ball& ball, const GameObject& obj)
{
    Point p = ball.topLeft();
    p.y = obj.topLeft().y - ball.height();
    ball.setTopLeft(p);
}

void putBeforeIntersectsWithTopY(Ball& ball, const GameObject& obj)
{
    Point p = ball.topLeft();
    p.y = obj.bottomRight().y;
    ball.setTopLeft(p);
}

types::Angle clampAngle(const types::Angle& angle)
{
    auto deltaX = 30.0_deg;
    auto deltaY = 15.0_deg;

    auto newAngle = angle;

    if (isBigger(angle.get(), 0.0_deg, deltaX)) {
        newAngle.set(0.0_deg + deltaX);
    }
    else if (isSmaller(angle.get(), 90.0_deg, deltaY)) {
        newAngle.set(90.0_deg - deltaY);
    }
    else if (isBigger(angle.get(), 90.0_deg, deltaY)) {
        newAngle.set(90.0_deg + deltaY);
    }
    else if (isSmaller(angle.get(), 180.0_deg, deltaX)) {
        newAngle.set(180.0_deg - deltaX);
    }
    else if (isBigger(angle.get(), 180.0_deg, deltaX)) {
        newAngle.set(180.0_deg + deltaX);
    }
    else if (isSmaller(angle.get(), 270.0_deg, deltaY)) {
        newAngle.set(270.0_deg - deltaY);
    }
    else if (isBigger(angle.get(), 270.0_deg, deltaY)) {
        newAngle.set(270.0_deg + deltaY);
    }
    else if (isSmaller(angle.get(), 360.0_deg, deltaX)) {
        newAngle.set(360.0_deg - deltaX);
    }

    return newAngle;
}

bool isSmaller(double angle, double targetAngle, double delta)
{
    return angle >= targetAngle - delta && angle < targetAngle;
}

bool isBigger(double angle, double targetAngle, double delta)
{
    return angle >= targetAngle && angle < targetAngle + delta;
}

} // namespace bricks::game_objects