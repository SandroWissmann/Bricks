#include "GameObjectPhysics.h"

#include "types/Angle.h"
#include "types/Point.h"

#include "Ball.h"
#include "GameObject.h"
#include "NearlyEqual.h"
#include "OperatorDegree.h"

#include <algorithm>
#include <random>

namespace bricks {

using Angle = types::Angle;
using Point = types::Point;
using Quadrant = types::Quadrant;

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
        if (isInsideWithX(ball, obj)) {
            reflectHorizontal(ball);
        }
        else if (interectsWithRightX(ball, obj) &&
                 notThroughWithRightX(ball, obj)) {
            reflectHorizontalIncreased(ball);
        }
        else if (interectsWithLeftX(ball, obj) &&
                 notThroughWithLeftX(ball, obj)) {
            reflectHorizontalIncreased(ball);
        }
        else {
            return false;
        }
        putBeforeIntersectsWithBottomY(ball, obj);
        ball.setAngle(clampAngle(ball.angle()));
        return true;
    }
    else if (interectsWithRightX(ball, obj)) {
        if (isInsideWithY(ball, obj)) {
            reflectVertical(ball);
        }
        else if (interectsWithBottomY(ball, obj) &&
                 notThroughWithBottomY(ball, obj)) {
            reflectVerticalIncreased(ball);
        }
        else if (interectsWithTopY(ball, obj) &&
                 notThroughWithTopY(ball, obj)) {
            reflectVerticalIncreased(ball);
        }
        else {
            return false;
        }
        putBeforeIntersectsWithRightX(ball, obj);
        ball.setAngle(clampAngle(ball.angle()));
        return true;
    }
    return false;
}

bool reflectFromQuadrantII(Ball& ball, const GameObject& obj)
{
    if (interectsWithBottomY(ball, obj)) {
        if (isInsideWithX(ball, obj)) {
            reflectHorizontal(ball);
        }
        else if (interectsWithRightX(ball, obj) &&
                 notThroughWithRightX(ball, obj)) {
            reflectHorizontalDecreased(ball);
        }
        else if (interectsWithLeftX(ball, obj) &&
                 notThroughWithLeftX(ball, obj)) {
            reflectHorizontalDecreased(ball);
        }
        else {
            return false;
        }
        putBeforeIntersectsWithBottomY(ball, obj);
        ball.setAngle(clampAngle(ball.angle()));
        return true;
    }
    else if (interectsWithLeftX(ball, obj)) {
        if (isInsideWithY(ball, obj)) {
            reflectVertical(ball);
        }
        else if (interectsWithBottomY(ball, obj) &&
                 notThroughWithBottomY(ball, obj)) {
            reflectVerticalDecreased(ball);
        }
        else if (interectsWithTopY(ball, obj) &&
                 notThroughWithTopY(ball, obj)) {
            reflectVerticalDecreased(ball);
        }
        else {
            return false;
        }
        putBeforeIntersectsWithLeftX(ball, obj);
        ball.setAngle(clampAngle(ball.angle()));
        return true;
    }
    return false;
}

bool reflectFromQuadrantIII(Ball& ball, const GameObject& obj)
{
    if (interectsWithTopY(ball, obj)) {
        if (isInsideWithX(ball, obj)) {
            reflectHorizontal(ball);
        }
        else if (interectsWithRightX(ball, obj) &&
                 notThroughWithRightX(ball, obj)) {
            reflectHorizontalIncreased(ball);
        }
        else if (interectsWithLeftX(ball, obj) &&
                 notThroughWithLeftX(ball, obj)) {
            reflectHorizontalIncreased(ball);
        }
        else {
            return false;
        }
        putBeforeIntersectsWithTopY(ball, obj);
        ball.setAngle(clampAngle(ball.angle()));
        return true;
    }
    else if (interectsWithLeftX(ball, obj)) {
        if (isInsideWithY(ball, obj)) {
            reflectVertical(ball);
        }
        else if (interectsWithBottomY(ball, obj) &&
                 notThroughWithBottomY(ball, obj)) {
            reflectVerticalIncreased(ball);
        }
        else if (interectsWithTopY(ball, obj) &&
                 notThroughWithTopY(ball, obj)) {
            reflectVerticalIncreased(ball);
        }
        else {
            return false;
        }
        putBeforeIntersectsWithLeftX(ball, obj);
        ball.setAngle(clampAngle(ball.angle()));
        return true;
    }
    return false;
}

bool reflectFromQuadrantIV(Ball& ball, const GameObject& obj)
{
    if (interectsWithTopY(ball, obj)) {
        if (isInsideWithX(ball, obj)) {
            reflectHorizontal(ball);
        }
        else if (interectsWithRightX(ball, obj) &&
                 notThroughWithRightX(ball, obj)) {
            reflectHorizontalDecreased(ball);
        }
        else if (interectsWithLeftX(ball, obj) &&
                 notThroughWithLeftX(ball, obj)) {
            reflectHorizontalDecreased(ball);
        }
        else {
            return false;
        }
        putBeforeIntersectsWithTopY(ball, obj);
        ball.setAngle(clampAngle(ball.angle()));
        return true;
    }
    else if (interectsWithRightX(ball, obj)) {
        if (isInsideWithY(ball, obj)) {
            reflectVertical(ball);
        }
        else if (interectsWithBottomY(ball, obj) &&
                 notThroughWithBottomY(ball, obj)) {
            reflectVerticalDecreased(ball);
        }
        else if (interectsWithTopY(ball, obj) &&
                 notThroughWithTopY(ball, obj)) {
            reflectVerticalDecreased(ball);
        }
        else {
            return false;
        }
        putBeforeIntersectsWithRightX(ball, obj);
        ball.setAngle(clampAngle(ball.angle()));
        return true;
    }
    return false;
}

types::Angle clampAngle(const types::Angle& angle)
{
    auto newAngle = angle;
    // if(angle.angle() > 150.0_deg) {
    //     newAngle.setAngle(150.0_deg);
    // }
    // else
    if (angle.angle() < 30.0_deg) {
        newAngle.setAngle(30.0_deg);
    }
    else if (angle.angle() <= 90.0_deg && angle.angle() > 75.0_deg) {
        newAngle.setAngle(75.0_deg);
    }
    else if (angle.angle() >= 90.0_deg && angle.angle() < 105.0_deg) {
        newAngle.setAngle(105.0_deg);
    }
    return newAngle;
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
    angle.setQuadrantAngle(increaseAngle(angle.quadrantAngle()));
    ball.setAngle(angle);
}

void reflectHorizontalDecreased(Ball& ball)
{
    auto angle = ball.angle();
    angle.mirrorHorizontal();
    angle.setQuadrantAngle(decreaseAngle(angle.quadrantAngle()));
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
    angle.setQuadrantAngle(increaseAngle(angle.quadrantAngle()));
    ball.setAngle(angle);
}

void reflectVerticalDecreased(Ball& ball)
{
    auto angle = ball.angle();
    angle.mirrorVertical();
    angle.setQuadrantAngle(decreaseAngle(angle.quadrantAngle()));
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

long double increaseAngle(long double quadrantAngle)
{
    quadrantAngle *= random(1.0L, 1.5L);

    return std::clamp(quadrantAngle, 0.0L, 60.0_deg);
}

long double decreaseAngle(long double quadrantAngle)
{
    return quadrantAngle * random(0.5L, 1.0L);
}

long double random(long double min, long double max)
{
    static std::default_random_engine e;
    static std::uniform_real_distribution<long double> dis(min, max);
    return dis(e);
}
} // namespace bricks
