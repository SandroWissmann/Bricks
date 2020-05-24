#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "types/Point.h"
#include "types/Length.h"
#include "types/Height.h"

namespace bricks {

class GameObject {
public:
    GameObject(types::Point topLeft, types::Length length, types::Height height);

    virtual ~GameObject() = 0;

    GameObject(const GameObject &) = default;
    GameObject(GameObject &&) = default;
    GameObject &operator=(const GameObject &other) = default;
    GameObject &operator=(GameObject &&other) = default;

    types::Point topLeft() const;
    virtual void setTopLeft(types::Point topLeft);
    types::Point bottomRight() const;

    double length() const;
    double height() const;

private:
    types::Point mTopLeft;

    const double mWidth;
    const double mHeight;
};

} // namespace bricks

#endif