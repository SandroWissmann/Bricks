#include "Renderer.h"

#include "Ball.h"
#include "Platform.h"
#include "Level.h"

#include <stdexcept>
#include <string>

namespace bricks {

Renderer::Renderer(const std::size_t screenWidth,
                   const std::size_t screenHeight, const std::size_t gridWidth,
                   const std::size_t gridHeight)
    : mScreenWidth{screenWidth}, mScreenHeight{screenHeight},
      mGridWidth{gridWidth}, mGridHeight{gridHeight}
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error(std::string{"Renderer\n"} + "SDL could not initialize.\n" +
                                 "SDL_Error: " + SDL_GetError() +"\n");
    }

    mSdlWindow = SDL_CreateWindow("Bricks", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, mScreenWidth,
                                  mScreenHeight, SDL_WINDOW_SHOWN);

    if (nullptr == mSdlWindow) {
        throw std::runtime_error(std::string{"Renderer\n"} +
                                 "Window could not be created.\n" +
                                 "SDL_Error: " + SDL_GetError() + "\n");
    }

    mSdlRenderer = SDL_CreateRenderer(mSdlWindow, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == mSdlRenderer) {
        throw std::runtime_error(std::string{"Renderer\n"} +
                                 "Renderer could not be created.\n" +
                                 "SDL_Error: " + SDL_GetError() + "\n");
    }
}

Renderer::~Renderer()
{
    SDL_DestroyWindow(mSdlWindow);
    SDL_Quit();
}

void Renderer::render(const Ball &ball, const Platform &platform,
                      const Level &level)
{
    SDL_Rect block;
    block.w = mScreenWidth / mGridWidth;
    block.h = mScreenHeight / mGridHeight;

    // clear screen
    SDL_SetRenderDrawColor(mSdlRenderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(mSdlRenderer);

      // Render ball
    SDL_SetRenderDrawColor(mSdlRenderer, 0xFF, 0xCC, 0x00, 0xFF);
    auto p = ball.topLeft();
    block.x = p.x * block.w * ball.length();
    block.y = p.y * block.h * ball.width();
    SDL_RenderFillRect(mSdlRenderer, &block);

    // Render Platform
    SDL_SetRenderDrawColor(mSdlRenderer, 0xFF, 0xCC, 0x00, 0xFF);
    auto p2 = platform.topLeft();
    block.x = p2.x * block.w * platform.length();
    block.y = p2.y * block.h * platform.width();
    SDL_RenderFillRect(mSdlRenderer, &block);

    // Update Screen
    SDL_RenderPresent(mSdlRenderer);
}

} // namespace bricks