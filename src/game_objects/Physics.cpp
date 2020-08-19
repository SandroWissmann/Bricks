#include "Physics.h"

#include "Ball.h"
#include "GameObject.h"
#include "Platform.h"

#include "../types/Angle.h"
#include "../types/Point.h"
#include "../utility/NearlyEqual.h"
#include "../utility/OperatorDegree.h"

#include <algorithm>
#include <random>

#include <iostream>

#include <cassert>

namespace bricks::game_objects {

using namespace utility;

using Angle = types::Angle;
using Point = types::Point;
using Quadrant = types::Quadrant;

bool reflect(Ball& ball, const Platform& platform)
{
    switch (ball.angle().quadrant()) {
    case Quadrant::I:
        return reflectFromQuadrantI(ball, platform);
    case Quadrant::II:
        return reflectFromQuadrantII(ball, platform);
    case Quadrant::III:
        return reflectFromQuadrantIII(ball, platform);
    case Quadrant::IV:
        return reflectFromQuadrantIV(ball, platform);
    }
    return false;
}

bool reflectFromQuadrantI(Ball& ball, const Platform& platform)
{
    if (interectsWithBottomY(ball, platform)) {
        return reflectHorizontalFromQuadrantI(ball, platform);
    }
    if (interectsWithRightX(ball, platform)) {
        return reflectVerticalFromQuadrantI(ball, platform);
    }
    return false;
}

bool reflectHorizontalFromQuadrantI(Ball& ball, const Platform& platform)
{
    if (isInsideWithX(ball, platform)) {
        reflectHorizontalItoIV(ball, platform);
    }
    else if (interectsWithRightX(ball, platform) &&
             notThroughWithRightX(ball, platform)) {
        reflectHorizontalItoIV(ball, platform);
    }
    else if (interectsWithLeftX(ball, platform) &&
             notThroughWithLeftX(ball, platform)) {
        reflectHorizontalItoIV(ball, platform);
    }
    else {
        return false;
    }
    putBeforeIntersectsWithBottomY(ball, platform);
    return true;
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

bool reflectFromQuadrantII(Ball& ball, const Platform& platform)
{
    if (interectsWithBottomY(ball, platform)) {
        return reflectHorizontalFromQuadrantII(ball, platform);
    }
    if (interectsWithLeftX(ball, platform)) {
        return reflectVerticalFromQuadrantII(ball, platform);
    }
    return false;
}

bool reflectHorizontalFromQuadrantII(Ball& ball, const Platform& platform)
{
    if (isInsideWithX(ball, platform)) {
        reflectHorizontalIItoIII(ball, platform);
    }
    else if (interectsWithRightX(ball, platform) &&
             notThroughWithRightX(ball, platform)) {
        reflectHorizontalIItoIII(ball, platform);
    }
    else if (interectsWithLeftX(ball, platform) &&
             notThroughWithLeftX(ball, platform)) {
        reflectHorizontalIItoIII(ball, platform);
    }
    else {
        return false;
    }
    putBeforeIntersectsWithBottomY(ball, platform);
    return true;
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

bool reflect(Ball& ball, const GameObject& obj)
{
    switch (ball.angle().quadrant()) {
    case Quadrant::I:
        return reflectFromQuadrantI(ball, obj);
    case Quadrant::II:
        return reflectFromQuadrantII(ball, obj);
    case Quadrant::III:
        return reflectFromQuadrantIII(ball, obj);
    case Quadrant::IV:
        return reflectFromQuadrantIV(ball, obj);
    }
    return false;
}

bool reflectFromQuadrantI(Ball& ball, const GameObject& obj)
{
    if (interectsWithBottomY(ball, obj)) {
        return reflectHorizontalFromQuadrantI(ball, obj);
    }
    if (interectsWithRightX(ball, obj)) {
        return reflectVerticalFromQuadrantI(ball, obj);
    }
    return false;
}

bool reflectHorizontalFromQuadrantI(Ball& ball, const GameObject& obj)
{
    if (isInsideWithX(ball, obj)) {
        reflectHorizontal(ball);
    }
    else if (interectsWithRightX(ball, obj) &&
             notThroughWithRightX(ball, obj)) {
        reflectHorizontalIncreased(ball);
    }
    else if (interectsWithLeftX(ball, obj) && notThroughWithLeftX(ball, obj)) {
        reflectHorizontalIncreased(ball);
    }
    else {
        return false;
    }
    putBeforeIntersectsWithBottomY(ball, obj);
    ball.setAngle(clampAngle(ball.angle()));
    return true;
}

bool reflectVerticalFromQuadrantI(Ball& ball, const GameObject& obj)
{
    if (isInsideWithY(ball, obj)) {
        reflectVertical(ball);
    }
    else if (interectsWithBottomY(ball, obj) &&
             notThroughWithBottomY(ball, obj)) {
        reflectVerticalIncreased(ball);
    }
    else if (interectsWithTopY(ball, obj) && notThroughWithTopY(ball, obj)) {
        reflectVerticalIncreased(ball);
    }
    else {
        return false;
    }
    putBeforeIntersectsWithRightX(ball, obj);
    ball.setAngle(clampAngle(ball.angle()));
    return true;
}

bool reflectFromQuadrantII(Ball& ball, const GameObject& obj)
{
    if (interectsWithBottomY(ball, obj)) {
        return reflectHorizontalFromQuadrantII(ball, obj);
    }
    if (interectsWithLeftX(ball, obj)) {
        return reflectVerticalFromQuadrantII(ball, obj);
    }
    return false;
}

bool reflectHorizontalFromQuadrantII(Ball& ball, const GameObject& obj)
{
    if (isInsideWithX(ball, obj)) {
        reflectHorizontal(ball);
    }
    else if (interectsWithRightX(ball, obj) &&
             notThroughWithRightX(ball, obj)) {
        reflectHorizontalDecreased(ball);
    }
    else if (interectsWithLeftX(ball, obj) && notThroughWithLeftX(ball, obj)) {
        reflectHorizontalDecreased(ball);
    }
    else {
        return false;
    }
    putBeforeIntersectsWithBottomY(ball, obj);
    ball.setAngle(clampAngle(ball.angle()));
    return true;
}

bool reflectVerticalFromQuadrantII(Ball& ball, const GameObject& obj)
{
    if (isInsideWithY(ball, obj)) {
        reflectVertical(ball);
    }
    else if (interectsWithBottomY(ball, obj) &&
             notThroughWithBottomY(ball, obj)) {
        reflectVerticalDecreased(ball);
    }
    else if (interectsWithTopY(ball, obj) && notThroughWithTopY(ball, obj)) {
        reflectVerticalDecreased(ball);
    }
    else {
        return false;
    }
    putBeforeIntersectsWithLeftX(ball, obj);
    ball.setAngle(clampAngle(ball.angle()));
    return true;
}

bool reflectFromQuadrantIII(Ball& ball, const GameObject& obj)
{
    if (interectsWithTopY(ball, obj)) {
        return reflectHorizontalFromQuadrantIII(ball, obj);
    }
    if (interectsWithLeftX(ball, obj)) {
        return reflectVerticalFromQuadrantIII(ball, obj);
    }
    return false;
}

bool reflectHorizontalFromQuadrantIII(Ball& ball, const GameObject& obj)
{
    if (isInsideWithX(ball, obj)) {
        reflectHorizontal(ball);
    }
    else if (interectsWithRightX(ball, obj) &&
             notThroughWithRightX(ball, obj)) {
        reflectHorizontalIncreased(ball);
    }
    else if (interectsWithLeftX(ball, obj) && notThroughWithLeftX(ball, obj)) {
        reflectHorizontalIncreased(ball);
    }
    else {
        return false;
    }
    putBeforeIntersectsWithTopY(ball, obj);
    ball.setAngle(clampAngle(ball.angle()));
    return true;
}

bool reflectVerticalFromQuadrantIII(Ball& ball, const GameObject& obj)
{
    if (isInsideWithY(ball, obj)) {
        reflectVertical(ball);
    }
    else if (interectsWithBottomY(ball, obj) &&
             notThroughWithBottomY(ball, obj)) {
        reflectVerticalIncreased(ball);
    }
    else if (interectsWithTopY(ball, obj) && notThroughWithTopY(ball, obj)) {
        reflectVerticalIncreased(ball);
    }
    else {
        return false;
    }
    putBeforeIntersectsWithLeftX(ball, obj);
    ball.setAngle(clampAngle(ball.angle()));
    return true;
}

bool reflectFromQuadrantIV(Ball& ball, const GameObject& obj)
{
    if (interectsWithTopY(ball, obj)) {
        return reflectHorizontalFromQuadrantIV(ball, obj);
    }
    if (interectsWithRightX(ball, obj)) {
        return reflectVerticalFromQuadrantIV(ball, obj);
    }
    return false;
}

bool reflectHorizontalFromQuadrantIV(Ball& ball, const GameObject& obj)
{
    if (isInsideWithX(ball, obj)) {
        reflectHorizontal(ball);
    }
    else if (interectsWithRightX(ball, obj) &&
             notThroughWithRightX(ball, obj)) {
        reflectHorizontalDecreased(ball);
    }
    else if (interectsWithLeftX(ball, obj) && notThroughWithLeftX(ball, obj)) {
        reflectHorizontalDecreased(ball);
    }
    else {
        return false;
    }
    putBeforeIntersectsWithTopY(ball, obj);
    ball.setAngle(clampAngle(ball.angle()));
    return true;
}

bool reflectVerticalFromQuadrantIV(Ball& ball, const GameObject& obj)
{
    if (isInsideWithY(ball, obj)) {
        reflectVertical(ball);
    }
    else if (interectsWithBottomY(ball, obj) &&
             notThroughWithBottomY(ball, obj)) {
        reflectVerticalDecreased(ball);
    }
    else if (interectsWithTopY(ball, obj) && notThroughWithTopY(ball, obj)) {
        reflectVerticalDecreased(ball);
    }
    else {
        return false;
    }
    putBeforeIntersectsWithRightX(ball, obj);
    ball.setAngle(clampAngle(ball.angle()));
    return true;
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

bool interectsWithRightX(const GameObject& a, const GameObject& b)
{
    return a.bottomRight().x >= b.topLeft().x && a.topLeft().x < b.topLeft().x;
}

bool interectsWithLeftX(const GameObject& a, const GameObject& b)
{
    return a.topLeft().x <= b.bottomRight().x &&
           a.bottomRight().x > b.bottomRight().x;
}

bool interectsWithTopY(const GameObject& a, const GameObject& b)
{
    return a.topLeft().y <= b.bottomRight().y &&
           a.bottomRight().y > b.bottomRight().y;
}

bool interectsWithBottomY(const GameObject& a, const GameObject& b)
{
    return a.bottomRight().y >= b.topLeft().y && a.topLeft().y < b.topLeft().y;
}

bool isInsideWithX(const Ball& ball, const GameObject& obj)
{
    return ball.topLeft().x >= obj.topLeft().x &&
           ball.bottomRight().x <= obj.bottomRight().x;
}

bool isInsideWithY(const Ball& ball, const GameObject& obj)
{
    return ball.topLeft().y >= obj.topLeft().y &&
           ball.bottomRight().y <= obj.bottomRight().y;
}

bool notThroughWithRightX(const GameObject& a, const GameObject& b)
{
    return a.bottomRight().x <= b.bottomRight().x;
}

bool notThroughWithLeftX(const GameObject& a, const GameObject& b)
{
    return a.topLeft().x >= b.topLeft().x;
}

bool notThroughWithTopY(const GameObject& a, const GameObject& b)
{
    return a.topLeft().y >= b.topLeft().y;
    ;
}

bool notThroughWithBottomY(const GameObject& a, const GameObject& b)
{
    return a.bottomRight().y <= b.bottomRight().y;
}

void reflectHorizontal(Ball& ball)
{
    auto angle = ball.angle();
    angle.mirrorHorizontal();
    ball.setAngle(angle);
}

void reflectHorizontalIncreased(Ball& ball)
{
    auto angle = ball.angle();
    angle.mirrorHorizontal();
    angle.setQuadrantAngle(increaseQuadrandAngle(angle.quadrantAngle()));
    ball.setAngle(angle);
}

void reflectHorizontalDecreased(Ball& ball)
{
    auto angle = ball.angle();
    angle.mirrorHorizontal();
    angle.setQuadrantAngle(decreaseQuadrantAngle(angle.quadrantAngle()));
    ball.setAngle(angle);
}

void reflectVertical(Ball& ball)
{
    auto angle = ball.angle();
    angle.mirrorVertical();
    ball.setAngle(angle);
}

void reflectVerticalIncreased(Ball& ball)
{
    auto angle = ball.angle();
    angle.mirrorVertical();
    angle.setQuadrantAngle(increaseQuadrandAngle(angle.quadrantAngle()));
    ball.setAngle(angle);
}

void reflectVerticalDecreased(Ball& ball)
{
    auto angle = ball.angle();
    angle.mirrorVertical();
    angle.setQuadrantAngle(decreaseQuadrantAngle(angle.quadrantAngle()));
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

long double increaseQuadrandAngle(long double quadrantAngle)
{
    quadrantAngle *= random(1.0L, 1.5L);

    return std::clamp(quadrantAngle, 0.0L, 60.0_deg);
}

long double decreaseQuadrantAngle(long double quadrantAngle)
{
    return quadrantAngle * random(0.5L, 1.0L);
}

long double random(long double min, long double max)
{
    static std::default_random_engine e;
    std::uniform_real_distribution<long double> dis(min, max);
    return dis(e);
}
} // namespace bricks::game_objects
