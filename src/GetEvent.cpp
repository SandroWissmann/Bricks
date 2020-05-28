#include "GetEvent.h"

#include "SDL.h"

namespace bricks {

Event getEvent()
{
    Event event = Event::none;
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_QUIT) {
            return event = Event::quit;
        }
    }

    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    if(keystates[SDL_SCANCODE_LEFT]) {
        return Event::left;
    }
    if(keystates[SDL_SCANCODE_RIGHT]) {
        return Event::right;
    }
    if(keystates[SDL_SCANCODE_SPACE]) {
        return Event::space;
    }
    if(keystates[SDL_SCANCODE_ESCAPE]) {
        return Event::escape;
    }
    return Event::none;
}
} // namespace bricks