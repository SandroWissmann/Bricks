#include "Renderer.h"

#include "Ball.h"
#include "Brick.h"
#include "IndestructibleBrick.h"
#include "Platform.h"
#include "Level.h"

#include <stdexcept>
#include <string>

#include <iostream>

namespace bricks {

Renderer::Renderer(const std::size_t screenWidth,
                   const std::size_t screenHeight, const std::size_t gridWidth,
                   const std::size_t gridHeight)
    : mScreenWidth{screenWidth}, mScreenHeight{screenHeight},
      mGridWidth{gridWidth}, mGridHeight{gridHeight},
      mWidthFactor{ static_cast<double>(mScreenWidth) / static_cast<double>(mGridWidth)},
    mHeightFactor{ static_cast<double>(mScreenHeight) / static_cast<double>(mGridHeight)}

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

    clearScreen();

    render(ball);

    render(platform);


    for(const auto& brick : level.bricks) {
        render(brick);
    }

    for(const auto& indestructibleBrick : level.indestructibleBricks) {
        render(indestructibleBrick);
    }

    updateScreen();
}

    void Renderer::clearScreen()
    {
        // clear screen
        SDL_SetRenderDrawColor(mSdlRenderer, 0x1E, 0x1E, 0x1E, 0xFF);
        SDL_RenderClear(mSdlRenderer);
    }

    void Renderer::updateScreen()
    {
        SDL_RenderPresent(mSdlRenderer);
    }

    void Renderer::render(const Ball &ball)
    {
        auto rect = toSDLRect(ball);
        SDL_SetRenderDrawColor(mSdlRenderer, 0xCC, 0xFF, 0xFF, 0xFF);
        SDL_RenderFillRect(mSdlRenderer, &rect);
    }

    void Renderer::render(const Platform &platform)
    {
        auto rect = toSDLRect(platform);
        SDL_SetRenderDrawColor(mSdlRenderer, 0xBF, 0xBF, 0xBF, 0xFF);
        SDL_RenderFillRect(mSdlRenderer, &rect);
    }

    void Renderer::render(const Brick& brick)
    {
        
    }

    void Renderer::render(const IndestructibleBrick& indestructibleBrick)
    {
        auto rect = toSDLRect(indestructibleBrick);
        SDL_SetRenderDrawColor(mSdlRenderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(mSdlRenderer, &rect);
    }

    SDL_Rect Renderer::toSDLRect(const GameObject& obj) const
    {
        SDL_Rect rect;
        rect.w = mWidthFactor * obj.length();
        rect.h = mHeightFactor * obj.width();
        auto p = obj.topLeft();
        rect.x = mWidthFactor * p.x;
        rect.y = mHeightFactor * p.y;
        return rect;
    }

} // namespace bricks