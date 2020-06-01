#ifndef GAME_OBJECTS_MOVEABLEGAMEOBJECT_H
#define GAME_OBJECTS_MOVEABLEGAMEOBJECT_H

#include "GameObject.h"

#include "../types/Velocity.h"

namespace bricks::game_objects {

class MoveableGameObject : public GameObject {
public:
    MoveableGameObject();

    MoveableGameObject(types::Point topLeft, types::Width width,
                       types::Height height, types::Velocity velocity);

    virtual ~MoveableGameObject() = default;

    MoveableGameObject(const MoveableGameObject&) = default;
    MoveableGameObject(MoveableGameObject&&) = default;
    MoveableGameObject& operator=(const MoveableGameObject& other) = default;
    MoveableGameObject& operator=(MoveableGameObject&& other) = default;

    virtual void move(double elapsedTimeInMS) = 0;

    double velocity() const;
    void setVelocity(double velocity);

private:
    double mVelocity;
};

} // namespace bricks::game_objects
#endif