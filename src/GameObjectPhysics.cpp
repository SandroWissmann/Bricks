#include "GameObjectPhysics.h"

#include "GameObject.h"
#include "NearlyEqual.h"
#include "OperatorDegree.h"
#include "Point.h"
#include "Angle.h"

#include <algorithm>
#include <random>

namespace bricks {

void move(GameObject &a, double elapsedTimeInMS, double gravity)
{
    auto p = a.topLeft();

    if (a.velocity() != 0.0) {
        p = calcNewPosition(a.topLeft(), a.velocity(), a.angle(), elapsedTimeInMS);
    }

    if (gravity != 0.0) {
        p = calcNewPosition(p, gravity, Angle{90.0_deg}, elapsedTimeInMS);
    }

    a.setTopLeft(p);
}

Point calcNewPosition(const Point &p, double velocity, Angle angle, 
    double elapsedTimeInMS)
{
    auto distance = calcTraveldWay(elapsedTimeInMS, velocity);
    auto traveldWay = calcDelta(angle, distance);

    return Point{p.x + traveldWay.x, p.y + traveldWay.y};
}

double calcTraveldWay(double deltaTimeMS, double velocityInS)
{
    return deltaTimeMS / 1000.0 * velocityInS;
}

Point calcDelta(Angle angle, double sideC)
{
    if (nearlyEqual(sideC, 0.0)) {
        return Point{0, 0};
    }

    auto sideA = sin(angle.quadrantAngle()) * sideC;
    auto sideB = cos(angle.quadrantAngle()) * sideC;

    Point ret;
    switch (angle.quadrant()) {
    case Quadrant::I:
        ret.x = sideB;
        ret.y = sideA;
        break;
    case Quadrant::II:
        ret.x = -sideA;
        ret.y = sideB;
        break;
    case Quadrant::III:
        ret.x = -sideB;
        ret.y = -sideA;
        break;
    case Quadrant::IV:
        ret.x = sideA;
        ret.y = -sideB;
        break;
    }
    return ret;
}

bool ifHitReflect(GameObject &a, const GameObject &b)
{
    auto oldQuadrant = a.angle().quadrant();

    switch (oldQuadrant) {
    case Quadrant::I:
        ifHitReflectFromQuadrantI(a, b);
        break;
    case Quadrant::II:
        ifHitReflectFromQuadrantII(a, b);
        break;
    case Quadrant::III:
        ifHitReflectFromQuadrantIII(a, b);
        break;
    case Quadrant::IV:
        ifHitReflectFromQuadrantIV(a, b);
        break;
    }

    return a.angle().quadrant() != oldQuadrant;
}

void ifHitReflectFromQuadrantI(GameObject &a, const GameObject &b)
{
    if (interectsWithBottomY(a, b)) {
        bool reflected = true;
        if (isInsideWithX(a, b)) {
            reflectHorizontal(a);
        }
        else if (intersectsFromRigthWithX(a, b)) {
            reflectHorizontalIncreased(a);
        }
        else if (intersectsFromLeftWithX(a, b)) {
            reflectHorizontalIncreased(a);
        }
        else {
            reflected = false;
        }
        if(reflected) {
            putBeforeIntersectsWithBottomY(a, b);
        }
    }
    else if (interectsWithRightX(a, b)) {
        bool reflected = true;
        if (isInsideWithY(a, b)) {
            reflectVertical(a);
        }
        else if (intersectsFromTopWithY(a, b)) {  
            reflectVerticalIncreased(a);
        }
        else if (intersectsFromBottomWithY(a, b)) {  
            reflectVerticalIncreased(a);
        }
        else {
            reflected = false;
        }
        if(reflected) {
            putBeforeIntersectsWithRightX(a, b);          
        }
    }
}

void ifHitReflectFromQuadrantII(GameObject &a, const GameObject &b)
{
    if (interectsWithBottomY(a, b)) {
        bool reflected = true;
        if (isInsideWithX(a, b)) {
            reflectHorizontal(a);
        }
        else if (intersectsFromRigthWithX(a, b)) {
            reflectHorizontalDecreased(a);
        }
        else if (intersectsFromLeftWithX(a, b)) {
            reflectHorizontalDecreased(a);
        }
        else {
            reflected = false;
        }
        if(reflected) {
            putBeforeIntersectsWithBottomY(a, b);           
        }
    }
    else if (interectsWithLeftX(a, b)) {
        bool reflected = true;
        if (isInsideWithY(a, b)) {
            reflectVertical(a);
        }
        else if (intersectsFromTopWithY(a, b)) {
            reflectVerticalDecreased(a);
        }
        else if (intersectsFromBottomWithY(a, b)) {
            reflectVerticalDecreased(a);
        }
        else {
            reflected = false;
        }
        if(reflected) {
            putBeforeIntersectsWithLeftX(a, b);           
        }
    }
}

void ifHitReflectFromQuadrantIII(GameObject &a, const GameObject &b)
{
    if (interectsWithTopY(a, b)) {
        bool reflected = true;       
        if (isInsideWithX(a, b)) {
            reflectHorizontal(a);
        }
        else if (intersectsFromRigthWithX(a, b)) {
            reflectHorizontalIncreased(a);
        }
        else if (intersectsFromLeftWithX(a, b)) {
            reflectHorizontalIncreased(a);
        }
        else {
            reflected = false;
        }
        if(reflected) {
            putBeforeIntersectsWithTopY(a, b);            
        }
    }
    else if (interectsWithLeftX(a, b)) {
        bool reflected = true;
        if (isInsideWithY(a, b)) {
            reflectVertical(a);
        }
        else if (intersectsFromTopWithY(a, b)) {  
            reflectVerticalIncreased(a);
        }
        else if (intersectsFromBottomWithY(a, b)) {  
            reflectVerticalIncreased(a);
        }
        else {
            reflected = false;
        }
        if(reflected) {
            putBeforeIntersectsWithLeftX(a, b);            
        }
    }
}

void ifHitReflectFromQuadrantIV(GameObject &a, const GameObject &b)
{
    if (interectsWithTopY(a, b)) {
        bool reflected = true;
        if (isInsideWithX(a, b)) {
            reflectHorizontal(a);
        }
        else if (intersectsFromRigthWithX(a, b)) {
            reflectHorizontalDecreased(a);
        }
        else if (intersectsFromLeftWithX(a, b)) {
            reflectHorizontalDecreased(a);
        }
        else {
            reflected = false;
        }
        if(reflected) {
            putBeforeIntersectsWithTopY(a, b);           
        }
    }
    else if (interectsWithRightX(a, b)) {
        bool reflected = true;
        if (isInsideWithY(a, b)) {
            reflectVertical(a);
        }
        else if (intersectsFromTopWithY(a, b)) {
            reflectVerticalDecreased(a);
        }
        else if (intersectsFromBottomWithY(a, b)) {
            reflectVerticalDecreased(a);
        }
        else {
            reflected = false;
        }
        if(reflected) {
            putBeforeIntersectsWithRightX(a, b);            
        }
    }
}

bool interectsWithRightX(const GameObject &a, const GameObject &b)
{
    return a.bottomRight().x >= b.topLeft().x && a.topLeft().x < b.topLeft().x;
}

bool interectsWithLeftX(const GameObject &a, const GameObject &b)
{
    return a.topLeft().x <= b.bottomRight().x &&
           a.bottomRight().x > b.bottomRight().x;
}

bool interectsWithBottomY(const GameObject &a, const GameObject &b)
{
    return a.bottomRight().y >= b.topLeft().y && a.topLeft().y < b.topLeft().y;
}

bool interectsWithTopY(const GameObject &a, const GameObject &b)
{
    return a.topLeft().y <= b.bottomRight().y &&
           a.bottomRight().y > b.bottomRight().y;
}

bool isInsideWithY(const GameObject &a, const GameObject &b)
{
    return a.topLeft().y >= b.topLeft().y &&
           a.bottomRight().y <= b.bottomRight().y;
}

bool isInsideWithX(const GameObject &a, const GameObject &b)
{
    return a.topLeft().x >= b.topLeft().x &&
           a.bottomRight().x <= b.bottomRight().x;
}

bool intersectsFromRigthWithX(const GameObject &a, const GameObject &b)
{
    return a.bottomRight().x >= b.topLeft().x &&
           a.bottomRight().x <= b.bottomRight().x &&
           a.topLeft().x < b.topLeft().x;
}

bool intersectsFromLeftWithX(const GameObject &a, const GameObject &b)
{
    return a.topLeft().x >= b.topLeft().x &&
           a.topLeft().x <= b.bottomRight().x &&
           a.bottomRight().x > b.bottomRight().x;
}

bool intersectsFromTopWithY(const GameObject &a, const GameObject &b)
{
    return a.bottomRight().y >= b.topLeft().y &&
           a.bottomRight().y <= b.bottomRight().y &&
           a.topLeft().y < b.topLeft().y;
}

bool intersectsFromBottomWithY(const GameObject &a, const GameObject &b)
{
    return a.topLeft().y >= b.topLeft().y &&
           a.topLeft().y <= b.bottomRight().y &&
           a.bottomRight().y > b.bottomRight().y;
}

void reflectHorizontal(GameObject &a)
{
    auto angle = a.angle();
    angle.mirrorHorizontal();
    a.setAngle(angle);
}

void reflectHorizontalIncreased(GameObject &a)
{
    auto angle = a.angle();
    angle.mirrorHorizontal();
    angle.setQuadrantAngle(increaseAngle(angle.quadrantAngle()));
    a.setAngle(angle);
}

void reflectHorizontalDecreased(GameObject &a)
{
    auto angle = a.angle();
    angle.mirrorHorizontal();
    angle.setQuadrantAngle(decreaseAngle(angle.quadrantAngle()));
    a.setAngle(angle);
}

void reflectVertical(GameObject &a)
{
    auto angle = a.angle();
    angle.mirrorVertical();
    a.setAngle(angle);
}

void reflectVerticalIncreased(GameObject &a)
{
    auto angle = a.angle();
    angle.mirrorVertical();
    angle.setQuadrantAngle(increaseAngle(angle.quadrantAngle()));
    a.setAngle(angle);
}

void reflectVerticalDecreased(GameObject &a)
{
    auto angle = a.angle();
    angle.mirrorVertical();
    angle.setQuadrantAngle(decreaseAngle(angle.quadrantAngle()));
    a.setAngle(angle);
}

void putBeforeIntersectsWithRightX(GameObject &a, const GameObject &b)
{
    Point p = a.topLeft();
    p.x = b.topLeft().x - a.width();
    a.setTopLeft(p);
}

void putBeforeIntersectsWithLeftX(GameObject &a, const GameObject &b)
{
    Point p = a.topLeft();
    p.x = b.bottomRight().x;
    a.setTopLeft(p);
}

void putBeforeIntersectsWithBottomY(GameObject &a, const GameObject &b)
{
    Point p = a.topLeft();
    p.y = b.topLeft().y - a.height();
    a.setTopLeft(p);
}

void putBeforeIntersectsWithTopY(GameObject &a, const GameObject &b)
{
    Point p = a.topLeft();
    p.y = b.bottomRight().y;
    a.setTopLeft(p);
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
