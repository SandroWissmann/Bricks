#ifndef PLATFORM_H
#define PLATFORM_H

#include "MoveableGameObject.h"

namespace bricks {

class Platform : public MoveableGameObject {
public:
    using MoveableGameObject::MoveableGameObject;
    ~Platform() override = default;

    Platform(const Platform &) = default;
    Platform(Platform &&) = default;
    Platform &operator=(const Platform &other) = default;
    Platform &operator=(Platform &&other) = default;

    void move(double elapsedTimeInMS) override;
};
} // namespace bricks
#endif