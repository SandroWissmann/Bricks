#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Point.h"

namespace bricks {

enum class Quadrant { I, II, III, IV };

struct MaxPositionX {
    double value;

    double operator()() const {
        return value;
    }
};

struct MaxPositionY {
    double value;

    double operator()() const {
        return value;
    }
};

struct Width {
    double value;

    double operator()() const {
        return value;
    }
};

struct Height {
    double value;

    double operator()() const {
        return value;
    }
};

struct Velocity {
    double value;

    double operator()() const {
        return value;
    }
};

struct Angle {
    long double value;

    long double operator()() const {
        return value;
    }
};


class GameObject {
public:
    GameObject(Point topLeft, MaxPositionX maxPositionX, MaxPositionY maxPositionY,
               Width width, Height height, Velocity velocity, Angle angle);

    virtual ~GameObject() = 0;

    GameObject(const GameObject &) = default;
    GameObject(GameObject &&) = default;
    GameObject &operator=(const GameObject &other) = default;
    GameObject &operator=(GameObject &&other) = default;

    Point topLeft() const;
    void setTopLeft(Point topLeft);
    Point bottomRight() const;

    double maxPositionX() const;
    double maxPositionY() const;

    double width() const;
    double height() const;

    double velocity() const;
    void setVelocity(double velocity);

    long double angle() const;
    void setAngle(long double angle);

    long double quadrantAngle() const;
    void setQuadrantAngle(long double quadrantAngle);

    Quadrant quadrant() const;
    void setQuadrant(Quadrant quadrant);

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

namespace impl {

Quadrant calcQuadrant(long double angle);

bool isInQuadrantI(long double angle);
bool isInQuadrantII(long double angle);
bool isInQuadrantIII(long double angle);
bool isInQuadrantIV(long double angle);

long double angleToQuadrantAngle(long double angle, Quadrant quadrant);

long double quadrantAngleToAngle(long double quadrantAngle, Quadrant quadrant);

long double calcAngleIfOver360(long double angle);

} // namespace impl

} // namespace bricks
#endif