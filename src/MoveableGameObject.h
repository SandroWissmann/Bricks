#ifndef MOVEABLEGAMEOBJECT_H
#define MOVEABLEGAMEOBJECT_H

#include "GameObject.h"

#include "types/MaxPositionX.h"
#include "types/MaxPositionY.h"
#include "types/Velocity.h"

namespace bricks {

class MoveableGameObject : public GameObject {
public:
    MoveableGameObject(types::Point topLeft, types::Width width, types::Height height,
                       types::MaxPositionX maxPositionX, types::MaxPositionY maxPositionY,
                       types::Velocity velocity);

    virtual ~MoveableGameObject() = default;

    MoveableGameObject(const MoveableGameObject &) = default;
    MoveableGameObject(MoveableGameObject &&) = default;
    MoveableGameObject &operator=(const MoveableGameObject &other) = default;
    MoveableGameObject &operator=(MoveableGameObject &&other) = default;

    virtual void move(double elapsedTimeInMS) = 0;

    void setTopLeft(types::Point topLeft) override;

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