#include "Platform.h"

namespace bricks::game_objects {

void Platform::move(double elapsedTimeInMS)
{
    if (velocity() == 0.0) {
        return;
    }
    auto deltaX = elapsedTimeInMS / 1000.0 * velocity();

    auto newPos = topLeft();
    newPos.x += deltaX;
    setTopLeft(newPos);
}

} // namespace bricks::game_objects