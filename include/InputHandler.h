#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

namespace bricks {

class Level;

namespace game_objects {
class Wall;
class Ball;
class Platform;
} // namespace game_objects

class InputHandler {
public:
    InputHandler();
    ~InputHandler() = default;

    InputHandler(const InputHandler&) = delete;
    InputHandler(InputHandler&&) = delete;
    InputHandler& operator=(const InputHandler&) = delete;
    InputHandler& operator=(InputHandler&&) = delete;

    void handleInput(Level& level, double elapsedTimeMS);

    bool isPaused() const;
    bool changedPauseState() const;
    bool isQuit() const;

private:
    enum class Event { none, quit, left, right, space, escape, p };

    static Event getEvent();
    void handleEvent(const Event& event, double elapsedTimeMS, Level& level);
    void handleEvent(const Event& event, double elapsedTimeMS,
                     const game_objects::Wall& leftWall,
                     const game_objects::Wall& rightWall,
                     game_objects::Ball& ball,
                     game_objects::Platform& platform);

    bool mPaused{false};
    bool mChangedPauseState{false};
    bool mQuit{false};
};

namespace impl {
void moveLeft(game_objects::Platform& platform, double elapsedTimeInMS);
void moveRight(game_objects::Platform& platform, double elapsedTimeInMS);

bool intersectsWithLeftX(const game_objects::Platform& platform,
                         const game_objects::Wall& wall);
bool intersectsWithRightX(const game_objects::Platform& platform,
                          const game_objects::Wall& wall);
void putBeforeIntersectsWithLeftX(game_objects::Platform& platform,
                                  const game_objects::Wall& wall);
void putBeforeIntersectsWithRightX(game_objects::Platform& platform,
                                   const game_objects::Wall& wall);
} // namespace impl

} // namespace bricks

#endif