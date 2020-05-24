#include "GameObjectPhysics.h"

#include "Angle.h"
#include "Ball.h"
#include "GameObject.h"
#include "NearlyEqual.h"
#include "OperatorDegree.h"
#include "Point.h"

#include <algorithm>
#include <random>

namespace bricks {

using Point = types::Point;
using Quadrant = types::Quadrant;


bool ifHitReflect(Ball &ball, const GameObject &obj)
{
    auto oldQuadrant = ball.angle().quadrant();

    switch (oldQuadrant) {
    case Quadrant::I:
        ifHitReflectFromQuadrantI(ball, obj);
        break;
    case Quadrant::II:
        ifHitReflectFromQuadrantII(ball, obj);
        break;
    case Quadrant::III:
        ifHitReflectFromQuadrantIII(ball, obj);
        break;
    case Quadrant::IV:
        ifHitReflectFromQuadrantIV(ball, obj);
        break;
    }

    return ball.angle().quadrant() != oldQuadrant;
}

void ifHitReflectFromQuadrantI(Ball &ball, const GameObject &obj)
{
    if (interectsWithBottomY(ball, obj)) {
        bool reflected = true;
        if (isInsideWithX(ball, obj)) {
            reflectHorizontal(ball);
        }
        else if (intersectsFromRigthWithX(ball, obj)) {
            reflectHorizontalIncreased(ball);
        }
        else if (intersectsFromLeftWithX(ball, obj)) {
            reflectHorizontalIncreased(ball);
        }
        else {
            reflected = false;
        }
        if (reflected) {
            putBeforeIntersectsWithBottomY(ball, obj);
        }
    }
    else if (interectsWithRightX(ball, obj)) {
        bool reflected = true;
        if (isInsideWithY(ball, obj)) {
            reflectVertical(ball);
        }
        else if (intersectsFromTopWithY(ball, obj)) {
            reflectVerticalIncreased(ball);
        }
        else if (intersectsFromBottomWithY(ball, obj)) {
            reflectVerticalIncreased(ball);
        }
        else {
            reflected = false;
        }
        if (reflected) {
            putBeforeIntersectsWithRightX(ball, obj);
        }
    }
}

void ifHitReflectFromQuadrantII(Ball &ball, const GameObject &obj)
{
    if (interectsWithBottomY(ball, obj)) {
        bool reflected = true;
        if (isInsideWithX(ball, obj)) {
            reflectHorizontal(ball);
        }
        else if (intersectsFromRigthWithX(ball, obj)) {
            reflectHorizontalDecreased(ball);
        }
        else if (intersectsFromLeftWithX(ball, obj)) {
            reflectHorizontalDecreased(ball);
        }
        else {
            reflected = false;
        }
        if (reflected) {
            putBeforeIntersectsWithBottomY(ball, obj);
        }
    }
    else if (interectsWithLeftX(ball, obj)) {
        bool reflected = true;
        if (isInsideWithY(ball, obj)) {
            reflectVertical(ball);
        }
        else if (intersectsFromTopWithY(ball, obj)) {
            reflectVerticalDecreased(ball);
        }
        else if (intersectsFromBottomWithY(ball, obj)) {
            reflectVerticalDecreased(ball);
        }
        else {
            reflected = false;
        }
        if (reflected) {
            putBeforeIntersectsWithLeftX(ball, obj);
        }
    }
}

void ifHitReflectFromQuadrantIII(Ball &ball, const GameObject &obj)
{
    if (interectsWithTopY(ball, obj)) {
        bool reflected = true;
        if (isInsideWithX(ball, obj)) {
            reflectHorizontal(ball);
        }
        else if (intersectsFromRigthWithX(ball, obj)) {
            reflectHorizontalIncreased(ball);
        }
        else if (intersectsFromLeftWithX(ball, obj)) {
            reflectHorizontalIncreased(ball);
        }
        else {
            reflected = false;
        }
        if (reflected) {
            putBeforeIntersectsWithTopY(ball, obj);
        }
    }
    else if (interectsWithLeftX(ball, obj)) {
        bool reflected = true;
        if (isInsideWithY(ball, obj)) {
            reflectVertical(ball);
        }
        else if (intersectsFromTopWithY(ball, obj)) {
            reflectVerticalIncreased(ball);
        }
        else if (intersectsFromBottomWithY(ball, obj)) {
            reflectVerticalIncreased(ball);
        }
        else {
            reflected = false;
        }
        if (reflected) {
            putBeforeIntersectsWithLeftX(ball, obj);
        }
    }
}

void ifHitReflectFromQuadrantIV(Ball &ball, const GameObject &obj)
{
    if (interectsWithTopY(ball, obj)) {
        bool reflected = true;
        if (isInsideWithX(ball, obj)) {
            reflectHorizontal(ball);
        }
        else if (intersectsFromRigthWithX(ball, obj)) {
            reflectHorizontalDecreased(ball);
        }
        else if (intersectsFromLeftWithX(ball, obj)) {
            reflectHorizontalDecreased(ball);
        }
        else {
            reflected = false;
        }
        if (reflected) {
            putBeforeIntersectsWithTopY(ball, obj);
        }
    }
    else if (interectsWithRightX(ball, obj)) {
        bool reflected = true;
        if (isInsideWithY(ball, obj)) {
            reflectVertical(ball);
        }
        else if (intersectsFromTopWithY(ball, obj)) {
            reflectVerticalDecreased(ball);
        }
        else if (intersectsFromBottomWithY(ball, obj)) {
            reflectVerticalDecreased(ball);
        }
        else {
            reflected = false;
        }
        if (reflected) {
            putBeforeIntersectsWithRightX(ball, obj);
        }
    }
}

bool interectsWithRightX(const Ball &ball, const GameObject &obj)
{
    return ball.bottomRight().x >= obj.topLeft().x &&
           ball.topLeft().x < obj.topLeft().x;
}

bool interectsWithLeftX(const Ball &ball, const GameObject &obj)
{
    return ball.topLeft().x <= obj.bottomRight().x &&
           ball.bottomRight().x > obj.bottomRight().x;
}

bool interectsWithBottomY(const Ball &ball, const GameObject &obj)
{
    return ball.bottomRight().y >= obj.topLeft().y &&
           ball.topLeft().y < obj.topLeft().y;
}

bool interectsWithTopY(const Ball &ball, const GameObject &obj)
{
    return ball.topLeft().y <= obj.bottomRight().y &&
           ball.bottomRight().y > obj.bottomRight().y;
}

bool isInsideWithY(const Ball &ball, const GameObject &obj)
{
    return ball.topLeft().y >= obj.topLeft().y &&
           ball.bottomRight().y <= obj.bottomRight().y;
}

bool isInsideWithX(const Ball &ball, const GameObject &obj)
{
    return ball.topLeft().x >= obj.topLeft().x &&
           ball.bottomRight().x <= obj.bottomRight().x;
}

bool intersectsFromRigthWithX(const Ball &ball, const GameObject &obj)
{
    return ball.bottomRight().x >= obj.topLeft().x &&
           ball.bottomRight().x <= obj.bottomRight().x &&
           ball.topLeft().x < obj.topLeft().x;
}

bool intersectsFromLeftWithX(const Ball &ball, const GameObject &obj)
{
    return ball.topLeft().x >= obj.topLeft().x &&
           ball.topLeft().x <= obj.bottomRight().x &&
           ball.bottomRight().x > obj.bottomRight().x;
}

bool intersectsFromTopWithY(const Ball &ball, const GameObject &obj)
{
    return ball.bottomRight().y >= obj.topLeft().y &&
           ball.bottomRight().y <= obj.bottomRight().y &&
           ball.topLeft().y < obj.topLeft().y;
}

bool intersectsFromBottomWithY(const Ball &ball, const GameObject &obj)
{
    return ball.topLeft().y >= obj.topLeft().y &&
           ball.topLeft().y <= obj.bottomRight().y &&
           ball.bottomRight().y > obj.bottomRight().y;
}

void reflectHorizontal(Ball &ball)
{
    auto angle = ball.angle();
    angle.mirrorHorizontal();
    ball.setAngle(angle);
}

void reflectHorizontalIncreased(Ball &ball)
{
    auto angle = ball.angle();
    angle.mirrorHorizontal();
    angle.setQuadrantAngle(increaseAngle(angle.quadrantAngle()));
    ball.setAngle(angle);
}

void reflectHorizontalDecreased(Ball &ball)
{
    auto angle = ball.angle();
    angle.mirrorHorizontal();
    angle.setQuadrantAngle(decreaseAngle(angle.quadrantAngle()));
    ball.setAngle(angle);
}

void reflectVertical(Ball &ball)
{
    auto angle = ball.angle();
    angle.mirrorVertical();
    ball.setAngle(angle);
}

void reflectVerticalIncreased(Ball &ball)
{
    auto angle = ball.angle();
    angle.mirrorVertical();
    angle.setQuadrantAngle(increaseAngle(angle.quadrantAngle()));
    ball.setAngle(angle);
}

void reflectVerticalDecreased(Ball &ball)
{
    auto angle = ball.angle();
    angle.mirrorVertical();
    angle.setQuadrantAngle(decreaseAngle(angle.quadrantAngle()));
    ball.setAngle(angle);
}

void putBeforeIntersectsWithRightX(Ball &ball, const GameObject &obj)
{
    Point p = ball.topLeft();
    p.x = obj.topLeft().x - ball.length();
    ball.setTopLeft(p);
}

void putBeforeIntersectsWithLeftX(Ball &ball, const GameObject &obj)
{
    Point p = ball.topLeft();
    p.x = obj.bottomRight().x;
    ball.setTopLeft(p);
}

void putBeforeIntersectsWithBottomY(Ball &ball, const GameObject &obj)
{
    Point p = ball.topLeft();
    p.y = obj.topLeft().y - ball.height();
    ball.setTopLeft(p);
}

void putBeforeIntersectsWithTopY(Ball &ball, const GameObject &obj)
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
