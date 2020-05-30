#ifndef GAME_OBJECTS_PHYSICS_H
#define GAME_OBJECTS_PHYSICS_H

namespace bricks::types {
class Angle;
}

namespace bricks::game_objects {

class Ball;
class GameObject;

bool reflect(Ball& ball, const GameObject& obj);

bool reflectFromQuadrantI(Ball& ball, const GameObject& obj);
bool reflectFromQuadrantII(Ball& ball, const GameObject& obj);
bool reflectFromQuadrantIII(Ball& ball, const GameObject& obj);
bool reflectFromQuadrantIV(Ball& ball, const GameObject& obj);

types::Angle clampAngle(const types::Angle& angle);

bool isSmaller(double angle, double targetAngle, double delta);
bool isBigger(double angle, double targetAngle, double delta);

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