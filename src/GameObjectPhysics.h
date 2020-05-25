#ifndef GAMEOBJECTPHYSICS_H
#define GAMEOBJECTPHYSICS_H

namespace bricks {

class Ball;
class GameObject;

bool ifHitReflect(Ball &ball, const GameObject &obj);

void ifHitReflectFromQuadrantI(Ball &ball, const GameObject &obj);
void ifHitReflectFromQuadrantII(Ball &ball, const GameObject &obj);
void ifHitReflectFromQuadrantIII(Ball &ball, const GameObject &obj);
void ifHitReflectFromQuadrantIV(Ball &ball, const GameObject &obj);

bool interectsWithRightX(const Ball &ball, const GameObject &obj);
bool interectsWithLeftX(const Ball &ball, const GameObject &obj);
bool interectsWithBottomY(const Ball &ball, const GameObject &obj);
bool interectsWithTopY(const Ball &ball, const GameObject &obj);

bool isInsideWithY(const Ball &ball, const GameObject &obj);
bool isInsideWithX(const Ball &ball, const GameObject &obj);

bool intersectsFromRigthWithX(const Ball &ball, const GameObject &obj);
bool intersectsFromLeftWithX(const Ball &ball, const GameObject &obj);
bool intersectsFromTopWithY(const Ball &ball, const GameObject &obj);
bool intersectsFromBottomWithY(const Ball &ball, const GameObject &obj);

void reflectHorizontal(Ball &ball);
void reflectHorizontalIncreased(Ball &ball);
void reflectHorizontalDecreased(Ball &ball);
void reflectVertical(Ball &ball);
void reflectVerticalIncreased(Ball &ball);
void reflectVerticalDecreased(Ball &ball);

void putBeforeIntersectsWithRightX(Ball &ball, const GameObject &obj);
void putBeforeIntersectsWithLeftX(Ball &ball, const GameObject &obj);
void putBeforeIntersectsWithBottomY(Ball &ball, const GameObject &obj);
void putBeforeIntersectsWithTopY(Ball &ball, const GameObject &obj);

long double increaseAngle(long double quadrantAngle);

long double decreaseAngle(long double quadrantAngle);

long double mirror(long double quadrantAngle);

long double random(long double min, long double max);
} // namespace bricks

#endif // GAMEOBJECTPHYSICS_H