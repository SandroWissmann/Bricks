#include "SDL_RAII.h"

#include <SDL.h>

#include <stdexcept>
#include <string>
#include <iostream>

namespace bricks {

void SDL_RAII::init()
{
    static SDL_RAII instance{};
}

SDL_RAII::SDL_RAII() { 
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        throw std::runtime_error(std::string{"Renderer\n"} +
                                "SDL could not initialize.\n" +
                                "SDL_Error: " + SDL_GetError() + "\n");
    }
}

SDL_RAII::~SDL_RAII() noexcept {
    try {
        SDL_Quit();
    } catch (...) {
        std::cerr<< "~SDL_RA\n"
        << "Unknown Exception on SDL_QUIT\n";
    }
}

}