#ifndef GAMEOBJECTPHYSICS_H
#define GAMEOBJECTPHYSICS_H

namespace bricks {

class Ball;
class GameObject;

bool ifHitReflect(Ball& ball, const GameObject& obj);

void ifHitReflectFromQuadrantI(Ball& ball, const GameObject& obj);
void ifHitReflectFromQuadrantII(Ball& ball, const GameObject& obj);
void ifHitReflectFromQuadrantIII(Ball& ball, const GameObject& obj);
void ifHitReflectFromQuadrantIV(Ball& ball, const GameObject& obj);

bool interectsWithRightX(const GameObject& a, const GameObject& b);
bool interectsWithLeftX(const GameObject& a, const GameObject& b);
bool interectsWithBottomY(const GameObject& a, const GameObject& b);
bool interectsWithTopY(const GameObject& a, const GameObject& b);

bool isInsideWithX(const Ball& ball, const GameObject& obj);
bool isInsideWithY(const Ball& ball, const GameObject& obj);

bool notThroughWithRightX(const GameObject& a, const GameObject& b);
bool notThroughWithLeftX(const GameObject& a, const GameObject& b);
bool notThroughWithTopY(const GameObject& a, const GameObject& b);
bool notThroughWithBottomY(const GameObject& a, const GameObject& b);

void reflectHorizontal(Ball& ball);
void reflectHorizontalIncreased(Ball& ball);
void reflectHorizontalDecreased(Ball& ball);
void reflectVertical(Ball& ball);
void reflectVerticalIncreased(Ball& ball);
void reflectVerticalDecreased(Ball& ball);

void putBeforeIntersectsWithRightX(GameObject& a, const GameObject& b);
void putBeforeIntersectsWithLeftX(GameObject& a, const GameObject& b);
void putBeforeIntersectsWithBottomY(Ball& ball, const GameObject& obj);
void putBeforeIntersectsWithTopY(Ball& ball, const GameObject& obj);

long double increaseAngle(long double quadrantAngle);

long double decreaseAngle(long double quadrantAngle);

long double mirror(long double quadrantAngle);

long double random(long double min, long double max);
} // namespace bricks

#endif // GAMEOBJECTPHYSICS_H