#ifndef GAME_OBJECTS_PHYSICS_H
#define GAME_OBJECTS_PHYSICS_H

namespace bricks::types {
class Angle;
}

namespace bricks::game_objects {

class Ball;
class GameObject;
class Platform;

bool reflect(Ball& ball, const Platform& platform);

bool reflectFromQuadrantI(Ball& ball, const Platform& platform);
bool reflectHorizontalFromQuadrantI(Ball& ball, const Platform& platform);
void reflectHorizontalItoIV(Ball& ball, const Platform& platform);

bool reflectFromQuadrantII(Ball& ball, const Platform& platform);
bool reflectHorizontalFromQuadrantII(Ball& ball, const Platform& platform);
void reflectHorizontalIItoIII(Ball& ball, const Platform& platform);

double calcAngleFactor(double xBall, double xLeft, double xCenter,
                       double xRight);

bool reflect(Ball& ball, const GameObject& obj);

bool reflectFromQuadrantI(Ball& ball, const GameObject& obj);

bool reflectHorizontalFromQuadrantI(Ball& ball, const GameObject& obj);
bool reflectVerticalFromQuadrantI(Ball& ball, const GameObject& obj);

bool reflectFromQuadrantII(Ball& ball, const GameObject& obj);

bool reflectHorizontalFromQuadrantII(Ball& ball, const GameObject& obj);
bool reflectVerticalFromQuadrantII(Ball& ball, const GameObject& obj);

bool reflectFromQuadrantIII(Ball& ball, const GameObject& obj);

bool reflectHorizontalFromQuadrantIII(Ball& ball, const GameObject& obj);
bool reflectVerticalFromQuadrantIII(Ball& ball, const GameObject& obj);

bool reflectFromQuadrantIV(Ball& ball, const GameObject& obj);

bool reflectHorizontalFromQuadrantIV(Ball& ball, const GameObject& obj);
bool reflectVerticalFromQuadrantIV(Ball& ball, const GameObject& obj);

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

long double increaseQuadrandAngle(long double quadrantAngle);

long double decreaseQuadrantAngle(long double quadrantAngle);

long double mirror(long double quadrantAngle);

long double random(long double min, long double max);
} // namespace bricks::game_objects

#endif // GAMEOBJECTPHYSICS_H