#include "InputHandler.h"

#include "game_objects/Ball.h"
#include "game_objects/Platform.h"
#include "game_objects/Wall.h"

#include "types/Point.h"

#include "Level.h"
#include "SDL_RAII.h"

#include <SDL.h>

namespace bricks {

using Ball = game_objects::Ball;
using Platform = game_objects::Platform;
using Wall = game_objects::Wall;

using Point = types::Point;

InputHandler::InputHandler()
{
    SDL_RAII::init();
}

void InputHandler::handleInput(Level& level, double elapsedTimeMS)
{
    auto event = getEvent();
    handleEvent(event, elapsedTimeMS, level);
}

bool InputHandler::isPaused() const
{
    return mPaused;
}

bool InputHandler::changedPauseState() const
{
    return mChangedPauseState;
}

bool InputHandler::isQuit() const
{
    return mQuit;
}

InputHandler::Event InputHandler::getEvent()
{
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent) != 0) {
        if (sdlEvent.type == SDL_QUIT) {
            return Event::quit;
        }
        if (sdlEvent.type == SDL_KEYDOWN) {
            if (sdlEvent.key.keysym.sym == SDLK_p) {
                return Event::p;
            }
        }
    }

    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    if (keystates[SDL_SCANCODE_LEFT] != 0U) {
        return Event::left;
    }
    if (keystates[SDL_SCANCODE_RIGHT] != 0U) {
        return Event::right;
    }
    if (keystates[SDL_SCANCODE_SPACE] != 0U) {
        return Event::space;
    }
    if (keystates[SDL_SCANCODE_ESCAPE] != 0U) {
        return Event::escape;
    }
    return Event::none;
}

void InputHandler::handleEvent(const InputHandler::Event& event,
                               double elapsedTimeMS, Level& level)
{
    handleEvent(event, elapsedTimeMS, level.leftWall(), level.rightWall(),
                level.ball, level.platform);
}

void InputHandler::handleEvent(const Event& event, double elapsedTimeMS,
                               const Wall& leftWall, const Wall& rightWall,
                               Ball& ball, Platform& platform)
{
    if (event == Event::p) {
        mPaused = !mPaused;
        mChangedPauseState = true;
        return;
    }
    mChangedPauseState = false;

    switch (event) {
    case Event::quit:
        [[fallthrough]];
    case Event::escape:
        mQuit = true;
        return;
    case Event::p:
        mPaused = !mPaused;
        return;
    }

    if (mPaused) {
        return;
    }

    switch (event) {
    case Event::space:
        if (!ball.isActive()) {
            ball.activate();
        }
        break;
    case Event::left:
        if (impl::intersectsWithLeftX(platform, leftWall)) {
            impl::putBeforeIntersectsWithLeftX(platform, leftWall);
        }
        else {
            impl::moveLeft(platform, elapsedTimeMS);
        }
        break;
    case Event::right:
        if (impl::intersectsWithRightX(platform, rightWall)) {
            impl::putBeforeIntersectsWithRightX(platform, rightWall);
        }
        else {
            impl::moveRight(platform, elapsedTimeMS);
        }
        break;
    }
}

namespace impl {
void moveLeft(Platform& platform, double elapsedTimeInMS)
{
    if (auto velocity = platform.velocity(); velocity > 0) {
        velocity *= -1;
        platform.setVelocity(velocity);
    }
    platform.move(elapsedTimeInMS);
}

void moveRight(Platform& platform, double elapsedTimeInMS)
{
    if (auto velocity = platform.velocity(); velocity < 0) {
        velocity *= -1;
        platform.setVelocity(velocity);
    }
    platform.move(elapsedTimeInMS);
}

bool intersectsWithLeftX(const Platform& platform, const Wall& wall)
{
    return platform.topLeft().x <= wall.bottomRight().x &&
           platform.bottomRight().x > wall.bottomRight().x;
}

bool intersectsWithRightX(const Platform& platform, const Wall& wall)
{
    return platform.bottomRight().x >= wall.topLeft().x &&
           platform.topLeft().x < wall.topLeft().x;
}

void putBeforeIntersectsWithLeftX(Platform& platform, const Wall& wall)
{
    auto p = platform.topLeft();
    p.x = wall.bottomRight().x;
    platform.setTopLeft(p);
}

void putBeforeIntersectsWithRightX(Platform& platform, const Wall& wall)
{
    auto p = platform.topLeft();
    p.x = wall.topLeft().x - platform.width();
    platform.setTopLeft(p);
}

} // namespace impl

} // namespace bricks