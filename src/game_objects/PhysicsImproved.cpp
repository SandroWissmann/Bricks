#include "PhysicsImproved.h"

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

namespace bricks::game_objects::improved {

using namespace utility;

using Angle = types::Angle;
using Point = types::Point;
using Quadrant = types::Quadrant;

bool reflectFromPlatform(const Ball& ball, const Platform& platform)
{
    return false;
}

std::vector<std::shared_ptr<GameObject>> reflectFromGameObjects(
    const Ball& ball, const std::vector<Wall>& walls,
    const std::vector<IndestructibleBrick>& indestructibleBrick,
    std::vector<Brick>& bricks)
{
    return std::vector<std::shared_ptr<GameObject>>{};
}

bool reflectFromSingleObject(const Ball& ball, const Platform& platform,
                             const Intersection& intersection)
{
}

bool reflectFromSingleObject(const Ball& ball, const GameObject& obj,
                             const Intersection& intersection)
{
    if
        intersection ==
            _Intersection.LEFT
            : _reflect_from_collision_with_left(ball, game_object)
                  elif intersection ==
            _Intersection.TOP_LEFT
            : if _intersection_is_more_left_than_top(ball, game_object)
            : _reflect_from_collision_with_left(ball, game_object) else
            : if isinstance(game_object, Platform)
            : _reflect_from_collision_with_top_relative_to_positon(
                  ball, game_object) else
            : _reflect_from_collision_with_top(ball, game_object)
                  elif intersection ==
            _Intersection.TOP : if isinstance(game_object, Platform)
            : _reflect_from_collision_with_top_relative_to_positon(
                  ball, game_object) else
            : _reflect_from_collision_with_top(ball, game_object)
                  elif intersection ==
            _Intersection.TOP_RIGHT
            : if _intersection_is_more_top_than_right(ball, game_object)
            : if isinstance(game_object, Platform)
            : _reflect_from_collision_with_top_relative_to_positon(
                  ball, game_object) else
            : _reflect_from_collision_with_top(ball, game_object) else
            : _reflect_from_collision_with_right(ball, game_object)
                  elif intersection ==
            _Intersection.RIGHT
            : _reflect_from_collision_with_right(ball, game_object)
                  elif intersection ==
            _Intersection.BOTTOM_RIGHT
            : if _intersection_is_more_right_than_bottom(ball, game_object)
            : _reflect_from_collision_with_right(ball, game_object) else
            : _reflect_from_collision_with_bottom(ball, game_object)
                  elif intersection ==
            _Intersection.BOTTOM
            : _reflect_from_collision_with_bottom(ball, game_object)
                  elif intersection ==
            _Intersection.BOTTOM_LEFT
            : if _intersection_is_more_bottom_than_left(ball, game_object)
            : _reflect_from_collision_with_bottom(ball, game_object) else
            : _reflect_from_collision_with_left(ball, game_object)
}

void reflectFromMultipleObjects(
    Ball& ball,
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs)
{
    assert(objectIntersectionPairs.size() > 1);

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
    auto isVariant1 =
        objectIntersectionPairsContainOnlyValuesFromIntersectionList(
            intersectionsVariant1, objectIntersectionPairs);
    if (isVariant1) {
        return true;
    }
    std::vector<Intersection> intersectionsVariant2{Intersection::topRight,
                                                    Intersection::bottom};
    auto isVariant2 =
        objectIntersectionPairsContainOnlyValuesFromIntersectionList(
            intersectionsVariant1, objectIntersectionPairs);
    return isVariant2;
}

bool intersectsInTopLeftCornerWithThreeObjects(
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs)
{
    assert(objectIntersectionPairs.size() == 3);

    std::vector<Intersection> intersections{Intersection::bottomLeft,
                                            Intersection::bottomRight,
                                            Intersection::topRight};

    return objectIntersectionPairsContainOnlyValuesFromIntersectionList(
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
    auto isVariant1 =
        objectIntersectionPairsContainOnlyValuesFromIntersectionList(
            intersectionsVariant1, objectIntersectionPairs);
    if (isVariant1) {
        return true;
    }
    std::vector<Intersection> intersectionsVariant2{Intersection::bottom,
                                                    Intersection::topLeft};
    auto isVariant2 =
        objectIntersectionPairsContainOnlyValuesFromIntersectionList(
            intersectionsVariant1, objectIntersectionPairs);
    return isVariant2;
}

bool intersectsInTopRightCornerWithThreeObjects(
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs)
{
    assert(objectIntersectionPairs.size() == 3);

    std::vector<Intersection> intersections{Intersection::bottomRight,
                                            Intersection::bottomLeft,
                                            Intersection::topLeft};

    return objectIntersectionPairsContainOnlyValuesFromIntersectionList(
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
    auto isVariant1 =
        objectIntersectionPairsContainOnlyValuesFromIntersectionList(
            intersectionsVariant1, objectIntersectionPairs);
    if (isVariant1) {
        return true;
    }
    std::vector<Intersection> intersectionsVariant2{Intersection::left,
                                                    Intersection::topRight};
    auto isVariant2 =
        objectIntersectionPairsContainOnlyValuesFromIntersectionList(
            intersectionsVariant1, objectIntersectionPairs);
    return isVariant2;
}

bool intersectsInBottomRightCornerWithThreeObjects(
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs)
{
    assert(objectIntersectionPairs.size() == 3);

    std::vector<Intersection> intersections{Intersection::topRight,
                                            Intersection::topLeft,
                                            Intersection::bottomLeft};

    return objectIntersectionPairsContainOnlyValuesFromIntersectionList(
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
    auto isVariant1 =
        objectIntersectionPairsContainOnlyValuesFromIntersectionList(
            intersectionsVariant1, objectIntersectionPairs);
    if (isVariant1) {
        return true;
    }
    std::vector<Intersection> intersectionsVariant2{Intersection::topLeft,
                                                    Intersection::right};
    auto isVariant2 =
        objectIntersectionPairsContainOnlyValuesFromIntersectionList(
            intersectionsVariant1, objectIntersectionPairs);
    return isVariant2;
}

bool intersectsInBottomLeftCornerWithThreeObjects(
    const std::vector<ObjectIntersectionPair>& objectIntersectionPairs)
{
    assert(objectIntersectionPairs.size() == 3);

    std::vector<Intersection> intersections{Intersection::topLeft,
                                            Intersection::topRight,
                                            Intersection::bottomRight};

    return objectIntersectionPairsContainOnlyValuesFromIntersectionList(
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

} // namespace bricks::game_objects::improved