#ifndef MOVEABLEGAMEOBJECT_H
#define MOVEABLEGAMEOBJECT_H

#include "GameObject.h"

namespace bricks {

struct MaxPositionX {
    double value;

    double operator()() const
    {
        return value;
    }
};

struct MaxPositionY {
    double value;

    double operator()() const
    {
        return value;
    }
};

struct Velocity {
    double value;

    double operator()() const
    {
        return value;
    }
};

class MoveableGameObject : public GameObject {
public:
    MoveableGameObject(Point topLeft, Width width, Height height,
                       MaxPositionX maxPositionX, MaxPositionY maxPositionY,
                       Velocity velocity);

    virtual ~MoveableGameObject() = default;

    MoveableGameObject(const MoveableGameObject &) = default;
    MoveableGameObject(MoveableGameObject &&) = default;
    MoveableGameObject &operator=(const MoveableGameObject &other) = default;
    MoveableGameObject &operator=(MoveableGameObject &&other) = default;

    virtual void move(double elapsedTimeInMS) = 0;

    void setTopLeft(Point topLeft) override;

    double maxPositionX() const;
    double maxPositionY() const;

    double velocity() const;
    void setVelocity(double velocity);

private:
    const double mMaxPositionX;
    const double mMaxPositionY;

    double mVelocity;
};

} // namespace bricks
#endif