#ifndef PLATFORM_H
#define PLATFORM_H

#include "MoveableGameObject.h"

namespace bricks {

class Platform : public GameObject {
public:
    using GameObject::GameObject;
    ~Platform() override = default;

    Platform(const Platform &) = default;
    Platform(Platform &&) = default;
    Platform &operator=(const Platform &other) = default;
    Platform &operator=(Platform &&other) = default;
};
} // namespace bricks
#endif