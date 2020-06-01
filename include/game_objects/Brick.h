#ifndef GAME_OBJECTS_BRICK_H
#define GAME_OBJECTS_BRICK_H

#include "GameObject.h"

#include "types/Hitpoints.h"

namespace bricks::game_objects {

class Brick : public GameObject {
public:
    Brick();
    Brick(types::Point topLeft, types::Width width, types::Height height,
          types::Hitpoints hitpoints);
    ~Brick() override = default;

    Brick(const Brick&) = default;
    Brick(Brick&&) = default;
    Brick& operator=(const Brick& other) = default;
    Brick& operator=(Brick&& other) = default;

    int startHitpoints() const;
    int hitpoints() const;

    void decreaseHitpoints();
    bool isDestroyed() const;

private:
    int checkArgs(int hitpoints);

    int mStartHitpoints;
    int mHitpoints;
};
} // namespace bricks::game_objects
#endif
