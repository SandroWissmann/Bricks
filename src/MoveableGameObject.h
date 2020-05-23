#ifndef MOVEABLEGAMEOBJECT_H
#define MOVEABLEGAMEOBJECT_H

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

struct Velocity {
    double value;

    double operator()() const { return value; }
};

class MoveableGameObject {
public:
    MoveableGameObject(Point topLeft, MaxPositionX maxPositionX,
               MaxPositionY maxPositionY, Width width, Height height,
               Velocity velocity, Angle angle);

    virtual ~MoveableGameObject() = 0;

    MoveableGameObject(const MoveableGameObject &) = default;
    MoveableGameObject(MoveableGameObject &&) = default;
    MoveableGameObject &operator=(const MoveableGameObject &other) = default;
    MoveableGameObject &operator=(MoveableGameObject &&other) = default;

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