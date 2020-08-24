#ifndef GAME_OBJECTS_GAMEOBJECT_H
#define GAME_OBJECTS_GAMEOBJECT_H

#include "../types/Height.h"
#include "../types/Point.h"
#include "../types/Width.h"

namespace bricks::game_objects {

class GameObject {
public:
    GameObject();
    GameObject(types::Point topLeft, types::Width width, types::Height height);

    virtual ~GameObject() = 0;

    GameObject(const GameObject&) = default;
    GameObject(GameObject&&) = default;
    GameObject& operator=(const GameObject& other) = default;
    GameObject& operator=(GameObject&& other) = default;

    types::Point topLeft() const;
    virtual void setTopLeft(types::Point topLeft);
    types::Point bottomRight() const;

    types::Point bottomLeft() const;
    types::Point topRight() const;

    double width() const;
    double height() const;

private:
    static types::Point checkArgs(types::Point point);

    types::Point mTopLeft;

    double mWidth;
    double mHeight;
};

} // namespace bricks::game_objects

#endif