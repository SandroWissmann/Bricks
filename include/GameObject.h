#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "types/Length.h"
#include "types/Point.h"
#include "types/Width.h"

namespace bricks {

class GameObject {
public:
    GameObject();
    GameObject(types::Point topLeft, types::Length length, types::Width width);

    virtual ~GameObject() = 0;

    GameObject(const GameObject&) = default;
    GameObject(GameObject&&) = default;
    GameObject& operator=(const GameObject& other) = default;
    GameObject& operator=(GameObject&& other) = default;

    types::Point topLeft() const;
    virtual void setTopLeft(types::Point topLeft);
    types::Point bottomRight() const;

    double length() const;
    double width() const;

private:
    types::Point mTopLeft;

    double mLength;
    double mWidth;
};

} // namespace bricks

#endif