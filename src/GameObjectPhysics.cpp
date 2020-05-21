#include "GameObjectPhysics.h"

#include "Point.h"
#include "GameObject.h"
#include "OperatorDegree.h"
#include "NearlyEqual.h"

#include <algorithm>
#include <random>

namespace bricks {

    void move(GameObject& a, double elapsedTimeInMS, double gravity)
    {
        auto p = a.topLeft();

        if(a.velocity() != 0.0) {
            p = calcNewPosition(
                a.topLeft(), a.velocity(), a.quadrant(), a.quadrantAngle(),
                elapsedTimeInMS);
        }

        if(gravity != 0.0) {
            p = calcNewPosition(p, gravity, Quadrant::I, 90.0_deg, 
            elapsedTimeInMS);
        }

        a.setTopLeft(p);
    }

    Point calcNewPosition(
        const Point& p, double velocity, Quadrant quadrant,
        double quadrantAngle, double elapsedTimeInMS)
    {
        auto distance = calcTraveldWay(elapsedTimeInMS, velocity);
        auto traveldWay = calcDelta(quadrantAngle, quadrant, distance);

        return Point{p.x + traveldWay.x, p.y + traveldWay.y};
    }


    bool ifHitReflect(GameObject& a, const GameObject& b)
    {
        auto oldQuadrant = a.quadrant();

        switch (oldQuadrant)
        {
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

        return a.quadrant() != oldQuadrant;
    }

    void ifHitReflectFromQuadrantI(GameObject& a, const GameObject& b)
    {
        if (interectsWithBottomY(a, b)) {
            ifIntersectsWithXreflectToQuadrantIV(a, b);
        }
        else if (interectsWithRightX(a, b)) {
            ifIntersectsWithYreflectToQuadrantII(a, b);
        }
    }

    void ifHitReflectFromQuadrantII(GameObject& a, const GameObject& b)
    {
        if (interectsWithLeftX(a, b)) {
            ifIntersectsWithYreflectToQuadrantI(a, b);
        }
        else if (interectsWithBottomY(a, b)) {
            ifIntersectsWithXreflectToQuadrantIII(a, b);
        }
    }

    void ifHitReflectFromQuadrantIII(GameObject& a, const GameObject& b)
    {
        if (interectsWithLeftX(a, b)) {
            ifIntersectsWithYreflectToQuadrantIV(a, b);
        }
        else if (interectsWithTopY(a, b)) {
            ifIntersectsWithXreflectToQuadrantII(a, b);
        }
    }

    void ifHitReflectFromQuadrantIV(GameObject& a, const GameObject& b)
    {
        if (interectsWithRightX(a, b)) {
            ifIntersectsWithYreflectToQuadrantIII(a, b);
        }
        else if (interectsWithTopY(a, b)) {
            ifIntersectsWithXreflectToQuadrantI(a, b);
        }
    }

    void ifIntersectsWithXreflectToQuadrantIV(
        GameObject& a, const GameObject& b)
    {
        if (isInsideWithX(a, b)) {
            toQuadrantIV(a);
        }
        else if (intersectsFromRigthWithX(a, b) ||
                 intersectsFromLeftWithX(a, b)) {
            toQuadrantIV(a);
            a.setQuadrantAngle(increaseAngle(a.quadrantAngle()));
        }
        else {
            return;
        }
        putBeforeIntersectsWithBottomY(a, b);
    }

    void ifIntersectsWithYreflectToQuadrantII(
        GameObject& a, const GameObject& b)
    {
        if (isInsideWithY(a, b)) {
            toQuadrantII(a);
        }
        else if (intersectsFromTopWithY(a, b) ||
                 intersectsFromBottomWithY(a, b)) {
            toQuadrantII(a);
            a.setQuadrantAngle(increaseAngle(a.quadrantAngle()));
        }
        else {
            return;
        }
        putBeforeIntersectsWithRightX(a, b);
    }

    void ifIntersectsWithXreflectToQuadrantIII(
        GameObject& a, const GameObject& b)
    {
        if (isInsideWithX(a, b)) {
            toQuadrantIII(a);
        }
        else if (intersectsFromRigthWithX(a, b) ||
                 intersectsFromLeftWithX(a, b)) {
            toQuadrantIII(a);
            a.setQuadrantAngle(decreaseAngle(a.quadrantAngle()));
        }
        else {
            return;
        }
        putBeforeIntersectsWithBottomY(a, b);
    }

    void ifIntersectsWithYreflectToQuadrantI(
        GameObject& a, const GameObject& b)
    {
        if (isInsideWithY(a, b)) {
            toQuadrantI(a);
        }
        else if (intersectsFromTopWithY(a, b) ||
                 intersectsFromBottomWithY(a, b)) {
            toQuadrantI(a);
            a.setQuadrantAngle(decreaseAngle(a.quadrantAngle()));
        }
        else {
            return;
        }
        putBeforeIntersectsWithLeftX(a, b);
    }

    void ifIntersectsWithXreflectToQuadrantII(
        GameObject& a, const GameObject& b)
    {
        if (isInsideWithX(a, b)) {
            toQuadrantII(a);
        }
        else if (intersectsFromRigthWithX(a, b) ||
                 intersectsFromLeftWithX(a, b)) {
            toQuadrantII(a);
            a.setQuadrantAngle(increaseAngle(a.quadrantAngle()));
        }
        else {
            return;
        }
        putBeforeIntersectsWithTopY(a, b);
    }

    void ifIntersectsWithYreflectToQuadrantIV(
        GameObject& a, const GameObject& b)
    {
        if (isInsideWithY(a, b)) {
            toQuadrantIV(a);
        }
        else if (intersectsFromTopWithY(a, b) ||
                 intersectsFromBottomWithY(a, b)) {
            toQuadrantIV(a);
            a.setQuadrantAngle(increaseAngle(a.quadrantAngle()));
        }
        else {
            return;
        }
        putBeforeIntersectsWithLeftX(a, b);
    }

    void ifIntersectsWithXreflectToQuadrantI(
        GameObject& a, const GameObject& b)
    {
        if (isInsideWithX(a, b)) {
            toQuadrantI(a);
        }
        else if (intersectsFromRigthWithX(a, b) ||
                 intersectsFromLeftWithX(a, b)) {
            toQuadrantI(a);
            a.setQuadrantAngle(decreaseAngle(a.quadrantAngle()));
        }
        else {
            return;
        }
        putBeforeIntersectsWithTopY(a, b);
    }

    void ifIntersectsWithYreflectToQuadrantIII(
        GameObject& a, const GameObject& b)
    {
        if (isInsideWithY(a, b)) {
            toQuadrantIII(a);
        }
        else if (intersectsFromTopWithY(a, b) ||
                 intersectsFromBottomWithY(a, b)) {
            toQuadrantIII(a);
            a.setQuadrantAngle(decreaseAngle(a.quadrantAngle()));
        }
        else {
            return;
        }
        putBeforeIntersectsWithRightX(a, b);
    }


    bool interectsWithRightX(const GameObject& a, const GameObject& b)
    {
        return a.bottomRight().x >= b.topLeft().x &&
               a.topLeft().x < b.topLeft().x;
    }

    void putBeforeIntersectsWithRightX(GameObject& a, const GameObject& b)
    {
        Point p = a.topLeft();
        p.x = b.topLeft().x - a.width();
        a.setTopLeft(p);
    }

    bool interectsWithLeftX(const GameObject& a, const GameObject& b)
    {
        return a.topLeft().x <= b.bottomRight().x &&
               a.bottomRight().x > b.bottomRight().x;
    }

    void putBeforeIntersectsWithLeftX(GameObject& a, const GameObject& b)
    {
        Point p = a.topLeft();
        p.x = b.bottomRight().x;
        a.setTopLeft(p);
    }

    bool interectsWithBottomY(const GameObject& a, const GameObject& b)
    {
        return a.bottomRight().y >= b.topLeft().y &&
               a.topLeft().y < b.topLeft().y;
    }

    void putBeforeIntersectsWithBottomY(GameObject& a, const GameObject& b)
    {
        Point p = a.topLeft();
        p.y = b.topLeft().y - a.height();
        a.setTopLeft(p);
    }

    bool interectsWithTopY(const GameObject& a, const GameObject& b)
    {
        return a.topLeft().y <= b.bottomRight().y &&
               a.bottomRight().y > b.bottomRight().y;
    }

    void putBeforeIntersectsWithTopY(GameObject& a, const GameObject& b)
    {
        Point p = a.topLeft();
        p.y = b.bottomRight().y;
        a.setTopLeft(p);
    }

    bool isInsideWithY(const GameObject& a, const GameObject& b)
    {
        return a.topLeft().y >= b.topLeft().y &&
               a.bottomRight().y <= b.bottomRight().y;
    }

    bool isInsideWithX(const GameObject& a, const GameObject& b)
    {
        return a.topLeft().x >= b.topLeft().x &&
               a.bottomRight().x <= b.bottomRight().x;
    }

    bool intersectsFromRigthWithX(const GameObject& a, const GameObject& b)
    {
        return a.bottomRight().x >= b.topLeft().x &&
               a.bottomRight().x <= b.bottomRight().x &&
               a.topLeft().x < b.topLeft().x;
    }

    bool intersectsFromLeftWithX(const GameObject& a, const GameObject& b)
    {
        return a.topLeft().x >= b.topLeft().x &&
               a.topLeft().x <= b.bottomRight().x &&
               a.bottomRight().x > b.bottomRight().x;
    }

    bool intersectsFromTopWithY(const GameObject& a, const GameObject& b)
    {
        return a.bottomRight().y >= b.topLeft().y &&
               a.bottomRight().y <= b.bottomRight().y &&
               a.topLeft().y < b.topLeft().y;
    }

    bool intersectsFromBottomWithY(const GameObject& a, const GameObject& b)
    {
        return a.topLeft().y >= b.topLeft().y &&
               a.topLeft().y <= b.bottomRight().y &&
               a.bottomRight().y > b.bottomRight().y;
    }

    void toQuadrantI(GameObject& obj)
    {
        obj.setQuadrant(Quadrant::I);
        obj.setQuadrantAngle(mirror(obj.quadrantAngle()));
    }

    void toQuadrantII(GameObject& obj)
    {
        obj.setQuadrant(Quadrant::II);
        obj.setQuadrantAngle(mirror(obj.quadrantAngle()));
    }

    void toQuadrantIII(GameObject& obj)
    {
        obj.setQuadrant(Quadrant::III);
        obj.setQuadrantAngle(mirror(obj.quadrantAngle()));
    }

    void toQuadrantIV(GameObject& obj)
    {
        obj.setQuadrant(Quadrant::IV);
        obj.setQuadrantAngle(mirror(obj.quadrantAngle()));
    }

    Point calcDelta(double quadrantAngle, Quadrant quadrant, double sideC)
    {
        if (nearlyEqual(sideC, 0.0)) {
            return Point{ 0,0 };
        }

        auto sideA = sin(quadrantAngle) * sideC;
        auto sideB = cos(quadrantAngle) * sideC;

        Point ret;
        switch (quadrant)
        {
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

    double calcTraveldWay(double deltaTimeMS, double velocityInS)
    {
        return deltaTimeMS / 1000.0 * velocityInS;
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

    long double mirror(long double quadrantAngle)
    {
        return 90.0_deg - quadrantAngle;
    }

    long double random(long double min, long double max)
    {
        static std::default_random_engine e;
        static std::uniform_real_distribution<long double> dis(min, max);
        return dis(e);
    }
}
