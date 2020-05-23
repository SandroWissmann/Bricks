#ifndef GAMEOBJECTPHYSICS_H
#define GAMEOBJECTPHYSICS_H

namespace bricks {

struct Point;
class Angle;
class MoveableGameObject;

void move(MoveableGameObject &a, double elapsedTimeInMS, double gravity = 0.0);

Point calcNewPosition(const Point &p, double velocity, Angle angle, 
    double elapsedTimeInMS);

double calcTraveldWay(double deltaTimeMS, double velocityInS);
Point calcDelta(Angle angle, double sideC);

bool ifHitReflect(MoveableGameObject &a, const MoveableGameObject &b);

void ifHitReflectFromQuadrantI(MoveableGameObject &a, const MoveableGameObject &b);
void ifHitReflectFromQuadrantII(MoveableGameObject &a, const MoveableGameObject &b);
void ifHitReflectFromQuadrantIII(MoveableGameObject &a, const MoveableGameObject &b);
void ifHitReflectFromQuadrantIV(MoveableGameObject &a, const MoveableGameObject &b);

bool interectsWithRightX(const MoveableGameObject &a, const MoveableGameObject &b);
bool interectsWithLeftX(const MoveableGameObject &a, const MoveableGameObject &b);
bool interectsWithBottomY(const MoveableGameObject &a, const MoveableGameObject &b);
bool interectsWithTopY(const MoveableGameObject &a, const MoveableGameObject &b);

bool isInsideWithY(const MoveableGameObject &a, const MoveableGameObject &b);
bool isInsideWithX(const MoveableGameObject &a, const MoveableGameObject &b);

bool intersectsFromRigthWithX(const MoveableGameObject &a, const MoveableGameObject &b);
bool intersectsFromLeftWithX(const MoveableGameObject &a, const MoveableGameObject &b);
bool intersectsFromTopWithY(const MoveableGameObject &a, const MoveableGameObject &b);
bool intersectsFromBottomWithY(const MoveableGameObject &a, const MoveableGameObject &b);

void reflectHorizontal(MoveableGameObject &a);
void reflectHorizontalIncreased(MoveableGameObject &a);
void reflectHorizontalDecreased(MoveableGameObject &a);
void reflectVertical(MoveableGameObject &a);
void reflectVerticalIncreased(MoveableGameObject &a);
void reflectVerticalDecreased(MoveableGameObject &a);

void putBeforeIntersectsWithRightX(MoveableGameObject &a, const MoveableGameObject &b);
void putBeforeIntersectsWithLeftX(MoveableGameObject &a, const MoveableGameObject &b);
void putBeforeIntersectsWithBottomY(MoveableGameObject &a, const MoveableGameObject &b);
void putBeforeIntersectsWithTopY(MoveableGameObject &a, const MoveableGameObject &b);

long double increaseAngle(long double quadrantAngle);

long double decreaseAngle(long double quadrantAngle);

long double mirror(long double quadrantAngle);

long double random(long double min, long double max);
} // namespace bricks

#endif // GAMEOBJECTPHYSICS_H