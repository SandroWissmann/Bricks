#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Angle.h"
#include "Point.h"

namespace bricks {

struct MaxPositionX {
    double value;

    double operator()() const { return value; }
};

struct MaxPositionY {
    double value;

    double operator()() const { return value; }
};

struct Width {
    double value;

    double operator()() const { return value; }
};

struct Height {
    double value;

    double operator()() const { return value; }
};

struct Velocity {
    double value;

    double operator()() const { return value; }
};

class GameObject {
public:
    GameObject(Point topLeft, MaxPositionX maxPositionX,
               MaxPositionY maxPositionY, Width width, Height height,
               Velocity velocity, Angle angle);

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

    Angle angle() const;
    void setAngle(Angle angle);

private:
    Point mTopLeft;
    const double mMaxPositionX;
    const double mMaxPositionY;

    const double mWidth;
    const double mHeight;

    double mVelocity;

    Angle mAngle;
};

} // namespace bricks
#endif