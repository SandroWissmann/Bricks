#include "IndestructibleBrick.h"

namespace bricks {

    IndestructibleBrick::IndestructibleBrick(
        Point topLeft, Width width, Height height)
        :GameObject(
            topLeft, 
            MaxPositionX{topLeft.x + width()}, 
            MaxPositionY{topLeft.y + height()},
            width, height, Velocity{0.0}, Angle{0.0})
    {
    }
}
