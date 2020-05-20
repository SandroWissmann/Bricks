#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Point.h"

namespace bricks {

enum class Quadrant { I, II, III, IV };

class GameObject {
public:
    GameObject(Point topLeft, double maxPositioX, double maxPositionY,
               double width, double height, double velocity, long double angle);

    virtual ~GameObject() = 0;

    GameObject(const GameObject &) = default;
    GameObject(GameObject &&) = default;
    GameObject &operator=(const GameObject &other) = default;
    GameObject &operator=(GameObject &&other) = default;

    Point topLeft() const;
    void setTopLeft(Point topLeft);
    Point bottomRight() const;

    double velocity() const;
    void setVelocity(double velocity);

    long double angle() const;
    void setAngle(long double angle);

    long double quadrantAngle() const;
    void setQuadrantAngle(long double quadrantAngle);

    Quadrant quadrant() const;
    void setQuadrant(Quadrant quadrant);

    double width() const;
    double height() const;

    double maxPositionX() const;
    double maxPositionY() const;

private:
    Point mTopLeft;
    const double mMaxPositionX;
    const double mMaxPositionY;

    const double mWidth;
    const double mHeight;

    double mVelocity;
    Quadrant mQuadrant;
    long double mQuadrantAngle;
};

bool isInQuadrantI(long double angle);
bool isInQuadrantII(long double angle);
bool isInQuadrantIII(long double angle);
bool isInQuadrantIV(long double angle);

Quadrant calcQuadrant(long double angle);

long double angleToQuadrantAngle(long double angle, Quadrant quadrant);

long double qudrantAngleToAngle(long double quadrantAngle, Quadrant quadrant);

long double calcAngleIfOver360(long double angle);

} // namespace bricks
#endif