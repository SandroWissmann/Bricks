#include "GetEvent.h"

#include "SDL.h"

namespace bricks {

Event getEvent()
{
    Event event = Event::none;
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_QUIT) {
            event = Event::quit;
        }
        else if (sdlEvent.type == SDL_KEYDOWN) {
            switch (sdlEvent.key.keysym.sym) {
            case SDLK_LEFT:
                event = Event::left;
                break;
            case SDLK_RIGHT:
                event = Event::right;
                break;
            case SDLK_SPACE:
                event = Event::space;
                break;
            case SDLK_ESCAPE:
                event = Event::escape;
                break;
            }
        }
    }
    return event;
}
} // namespace bricks