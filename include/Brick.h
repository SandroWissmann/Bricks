#ifndef BRICK_H
#define BRICK_H

#include "GameObject.h"

#include "types/Hitpoints.h"

namespace bricks {

class Brick : public GameObject {
public:
    Brick();
    Brick(types::Point topLeft, types::Length length, types::Width width,
          types::Hitpoints hitpoints);
    ~Brick() override = default;

    Brick(const Brick &) = default;
    Brick(Brick &&) = default;
    Brick &operator=(const Brick &other) = default;
    Brick &operator=(Brick &&other) = default;

    int startHitpoints() const;
    int hitpoints() const;

    void decreaseHitpoints();
    bool isDestroyed() const;

private:
    const int mStartHitpoints;
    int mHitpoints;
};
} // namespace bricks
#endif
