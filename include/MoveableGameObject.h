#ifndef MOVEABLEGAMEOBJECT_H
#define MOVEABLEGAMEOBJECT_H

#include "GameObject.h"

#include "types/MaxPositionX.h"
#include "types/MaxPositionY.h"
#include "types/Velocity.h"

namespace bricks {

class MoveableGameObject : public GameObject {
public:
    MoveableGameObject();

    MoveableGameObject(types::Point topLeft, types::Length length,
                       types::Width width, types::MaxPositionX maxPositionX,
                       types::MaxPositionY maxPositionY,
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
    double mMaxPositionX;
    double mMaxPositionY;

    double mVelocity;
};

} // namespace bricks
#endif