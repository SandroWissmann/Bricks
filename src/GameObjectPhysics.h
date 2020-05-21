#ifndef GAMEOBJECTPHYSICS_H
#define GAMEOBJECTPHYSICS_H

namespace bricks {

    struct Point;
    enum class Quadrant;
    class GameObject;

    void move(GameObject& a, double elapsedTimeInMS, double gravity = 0.0);

    Point calcNewPosition(
        const Point& p, double velocity, Quadrant quadrant,
        double quadrantAngle, double elapsedTimeInMS);


    bool ifHitReflect(GameObject& a, const GameObject& b);

    void ifHitReflectFromQuadrantI(GameObject& a, const GameObject& b);
    void ifHitReflectFromQuadrantII(GameObject& a, const GameObject& b);
    void ifHitReflectFromQuadrantIII(GameObject& a, const GameObject& b);
    void ifHitReflectFromQuadrantIV(GameObject& a, const GameObject& b);

    void ifIntersectsWithXreflectToQuadrantIV(
        GameObject& a, const GameObject& b);
    void ifIntersectsWithYreflectToQuadrantII(
        GameObject& a, const GameObject& b);

    void ifIntersectsWithXreflectToQuadrantIII(
        GameObject& a, const GameObject& b);
    void ifIntersectsWithYreflectToQuadrantI(
        GameObject& a, const GameObject& b);

    void ifIntersectsWithXreflectToQuadrantII(
        GameObject& a, const GameObject& b);
    void ifIntersectsWithYreflectToQuadrantIV(
        GameObject& a, const GameObject& b);

    void ifIntersectsWithXreflectToQuadrantI(
        GameObject& a, const GameObject& b);
    void ifIntersectsWithYreflectToQuadrantIII(
        GameObject& a, const GameObject& b);

    bool interectsWithRightX(const GameObject& a, const GameObject& b);
    void putBeforeIntersectsWithRightX(GameObject& a, const GameObject& b);

    bool interectsWithLeftX(const GameObject& a, const GameObject& b);
    void putBeforeIntersectsWithLeftX(GameObject& a, const GameObject& b);

    bool interectsWithBottomY(const GameObject& a, const GameObject& b);
    void putBeforeIntersectsWithBottomY(GameObject& a, const GameObject& b);

    bool interectsWithTopY(const GameObject& a, const GameObject& b);
    void putBeforeIntersectsWithTopY(GameObject& a, const GameObject& b);

    bool isInsideWithY(const GameObject& a, const GameObject& b);
    bool isInsideWithX(const GameObject& a, const GameObject& b);

    bool intersectsFromRigthWithX(const GameObject& a, const GameObject& b);
    bool intersectsFromLeftWithX(const GameObject& a, const GameObject& b);
    bool intersectsFromTopWithY(const GameObject& a, const GameObject& b);
    bool intersectsFromBottomWithY(const GameObject& a, const GameObject& b);

    void toQuadrantI(GameObject& obj);
    void toQuadrantII(GameObject& obj);
    void toQuadrantIII(GameObject& obj);
    void toQuadrantIV(GameObject& obj);

    Point calcDelta(double quadrantAngle, Quadrant quadrant, double sideC);

    double calcTraveldWay(double deltaTimeMS, double velocityInS);

    long double increaseAngle(long double quadrantAngle);

    long double decreaseAngle(long double quadrantAngle);

    long double mirror(long double quadrantAngle);

    long double random(long double min, long double max);
}

#endif // GAMEOBJECTPHYSICS_H