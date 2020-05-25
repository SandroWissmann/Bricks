#include "Renderer.h"

#include <iostream>

namespace bricks {

Renderer::Renderer(const std::size_t screenWidth,
                   const std::size_t screenHeight, const std::size_t gridWidth,
                   const std::size_t gridHeight)
    : mScreenWidth{screenWidth}, mScreenHeight{mScreenHeight},
      mGridWidth{gridWidth}, mGridHeight{gridHeight}
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // throw std::runtime_error("Renderer\n" + "SDL could not initialize.\n" +
        //                          "SDL_Error: " + SDL_GetError() +"\n");
    }

    mSdlWindow = SDL_CreateWindow("Bricks", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, mScreenWidth,
                                  mScreenHeight, SDL_WINDOW_SHOWN);

    if (nullptr == mSdlWindow) {
        // throw std::runtime_error("Renderer\n" +
        //                          "Window could not be created.\n" +
        //                          "SDL_Error: " + SDL_GetError() + "\n");
    }

    mSdlRenderer = SDL_CreateRenderer(mSdlWindow, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == mSdlRenderer) {
        // throw std::runtime_error("Renderer\n" +
        //                          "Renderer could not be created.\n" +
        //                          "SDL_Error: " + SDL_GetError() + "\n");
    }
}

Renderer::~Renderer()
{
    SDL_DestroyWindow(mSdlWindow);
    SDL_Quit();
}

void Renderer::Render(const Ball &ball, const Platform &platform,
                      const Level &level)
{
}
} // namespace bricks