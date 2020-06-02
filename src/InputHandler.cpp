#include "InputHandler.h"

#include "game_objects/Ball.h"
#include "game_objects/Platform.h"
#include "game_objects/Wall.h"

#include "game_objects/Physics.h"

#include "Level.h"
#include "SDL_RAII.h"

#include <SDL.h>

namespace bricks {

using Ball = game_objects::Ball;
using Platform = game_objects::Platform;
using Wall = game_objects::Wall;

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
    Event event = Event::none;
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent) != 0) {
        if (sdlEvent.type == SDL_QUIT) {
            return event = Event::quit;
        }
        if (sdlEvent.type == SDL_KEYDOWN) {
            if (sdlEvent.key.keysym.sym == SDLK_p) {
                return Event::p;
            }
        }
    }

    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    if (keystates[SDL_SCANCODE_LEFT] != 0u) {
        return Event::left;
    }
    if (keystates[SDL_SCANCODE_RIGHT] != 0u) {
        return Event::right;
    }
    if (keystates[SDL_SCANCODE_SPACE] != 0u) {
        return Event::space;
    }
    if (keystates[SDL_SCANCODE_ESCAPE] != 0u) {
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
        if (interectsWithLeftX(platform, leftWall)) {
            putBeforeIntersectsWithLeftX(platform, leftWall);
        }
        else {
            impl::moveLeft(platform, elapsedTimeMS);
        }
        break;
    case Event::right:
        if (interectsWithRightX(platform, rightWall)) {
            putBeforeIntersectsWithRightX(platform, rightWall);
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
} // namespace impl

} // namespace bricks