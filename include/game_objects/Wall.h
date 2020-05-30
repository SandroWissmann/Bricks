#ifndef GAME_OBJECTS_WALL_H
#define GAME_OBJECTS_WALL_H

#include "GameObject.h"

namespace bricks::game_objects {

class Wall : public GameObject {
public:
    using GameObject::GameObject;
    ~Wall() override = default;

    Wall(const Wall&) = default;
    Wall(Wall&&) = default;
    Wall& operator=(const Wall& other) = default;
    Wall& operator=(Wall&& other) = default;
};
} // namespace bricks
#endif