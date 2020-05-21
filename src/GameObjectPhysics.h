#ifndef GAMEOBJECTPHYSICS_H
#define GAMEOBJECTPHYSICS_H

namespace bricks {

struct Point;
class Angle;
class GameObject;

void move(GameObject &a, double elapsedTimeInMS, double gravity = 0.0);

Point calcNewPosition(const Point &p, double velocity, Angle angle, 
    double elapsedTimeInMS);

double calcTraveldWay(double deltaTimeMS, double velocityInS);
Point calcDelta(Angle angle, double sideC);

bool ifHitReflect(GameObject &a, const GameObject &b);

void ifHitReflectFromQuadrantI(GameObject &a, const GameObject &b);
void ifHitReflectFromQuadrantII(GameObject &a, const GameObject &b);
void ifHitReflectFromQuadrantIII(GameObject &a, const GameObject &b);
void ifHitReflectFromQuadrantIV(GameObject &a, const GameObject &b);

bool interectsWithRightX(const GameObject &a, const GameObject &b);
bool interectsWithLeftX(const GameObject &a, const GameObject &b);
bool interectsWithBottomY(const GameObject &a, const GameObject &b);
bool interectsWithTopY(const GameObject &a, const GameObject &b);

bool isInsideWithY(const GameObject &a, const GameObject &b);
bool isInsideWithX(const GameObject &a, const GameObject &b);

bool intersectsFromRigthWithX(const GameObject &a, const GameObject &b);
bool intersectsFromLeftWithX(const GameObject &a, const GameObject &b);
bool intersectsFromTopWithY(const GameObject &a, const GameObject &b);
bool intersectsFromBottomWithY(const GameObject &a, const GameObject &b);

void reflectHorizontal(GameObject &a);
void reflectHorizontalIncreased(GameObject &a);
void reflectHorizontalDecreased(GameObject &a);
void reflectVertical(GameObject &a);
void reflectVerticalIncreased(GameObject &a);
void reflectVerticalDecreased(GameObject &a);

void putBeforeIntersectsWithRightX(GameObject &a, const GameObject &b);
void putBeforeIntersectsWithLeftX(GameObject &a, const GameObject &b);
void putBeforeIntersectsWithBottomY(GameObject &a, const GameObject &b);
void putBeforeIntersectsWithTopY(GameObject &a, const GameObject &b);

long double increaseAngle(long double quadrantAngle);

long double decreaseAngle(long double quadrantAngle);

long double mirror(long double quadrantAngle);

long double random(long double min, long double max);
} // namespace bricks

#endif // GAMEOBJECTPHYSICS_H