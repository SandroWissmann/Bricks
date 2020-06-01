#include "Renderer.h"

#include "game_objects/Ball.h"
#include "game_objects/Brick.h"
#include "game_objects/IndestructibleBrick.h"
#include "game_objects/Platform.h"
#include "game_objects/Wall.h"

#include "types/RGBColor.h"

#include "Level.h"
#include "SDL_RAII.h"

#include <array>
#include <cassert>
#include <stdexcept>
#include <string>

#include <iostream>

namespace bricks {

using Ball = game_objects::Ball;
using Brick = game_objects::Brick;
using GameObject = game_objects::GameObject;
using IndestructibleBrick = game_objects::IndestructibleBrick;
using Platform = game_objects::Platform;
using Wall = game_objects::Wall;

using RGBColor = types::RGBColor;

Renderer::Renderer(const std::size_t screenWidth,
                   const std::size_t screenHeight, const std::size_t gridWidth,
                   const std::size_t gridHeight)
    : mScreenWidth{screenWidth}, mScreenHeight{screenHeight},
      mGridWidth{gridWidth}, mGridHeight{gridHeight},
      mWidthFactor{static_cast<double>(mScreenWidth) /
                   static_cast<double>(mGridWidth)},
      mHeightFactor{static_cast<double>(mScreenHeight) /
                    static_cast<double>(mGridHeight)}
    {

    SDL_RAII::init();

    mSdlWindow = std::unique_ptr<SDL_Window, SDLWindowDeleter>(
        SDL_CreateWindow("Bricks", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, mScreenWidth, mScreenHeight, SDL_WINDOW_SHOWN));

    if (mSdlWindow == nullptr) {
        throw std::runtime_error(std::string{"Renderer\n"} +
                                 "Window could not be created.\n" +
                                 "SDL_Error: " + SDL_GetError() + "\n");
    }

    mSdlRenderer = std::unique_ptr<SDL_Renderer, SDLRendererDeleter>(
        SDL_CreateRenderer(mSdlWindow.get(), -1, SDL_RENDERER_ACCELERATED));
    if (mSdlRenderer == nullptr) {
        throw std::runtime_error(std::string{"Renderer\n"} +
                                 "Renderer could not be created.\n" +
                                 "SDL_Error: " + SDL_GetError() + "\n");
    }
}

void Renderer::render(const Level& level)
{
    clearScreen();
    render(level.ball);
    render(level.platform);
    render(level.leftWall());
    render(level.rightWall());
    render(level.topWall());

    for (const auto& brick : level.bricks) {
        render(brick);
    }
    for (const auto& indestructibleBrick : level.indestructibleBricks) {
        render(indestructibleBrick);
    }
    updateScreen();
}

void Renderer::setWindowTitle(const std::string& title)
{
    SDL_SetWindowTitle(mSdlWindow.get(), title.c_str());
}

void Renderer::setPause()
{
    mPaused = true;
}

void Renderer::resetPause()
{
    mPaused = false;
}

void Renderer::clearScreen()
{
    RGBColor white{0x1E, 0x1E, 0x1E};

    if(!mPaused) {
        setDrawColor(white);
    }
    else {
        setDrawColor(white.grayscale());
    }
    SDL_RenderClear(mSdlRenderer.get());
}

void Renderer::updateScreen()
{
    SDL_RenderPresent(mSdlRenderer.get());
}

void Renderer::render(const Ball& ball)
{
    RGBColor lightBlue{0xCC, 0xFF, 0xFF};
    render(ball, lightBlue);
}

void Renderer::render(const Platform& platform)
{
    RGBColor gray{0xBF, 0xBF, 0xBF};
    render(platform, gray);
}

void Renderer::render(const Wall& wall)
{
    RGBColor brown{0xBF, 0x80, 0x40};
    render(wall, brown);
}

void Renderer::render(const Brick& brick)
{
    if (brick.isDestroyed()) {
        return;
    }
    auto color = getBrickDrawColor(brick);
    render(brick, color);
}

void Renderer::render(const IndestructibleBrick& indestructibleBrick)
{
    RGBColor red{0xFF, 0x00, 0x00};
    render(indestructibleBrick, red);
}

void Renderer::render(const GameObject& obj, RGBColor color)
{
    if(mPaused) {
        color = color.grayscale();
    }
    setDrawColor(color);
    auto rect = toSDLRect(obj);
    SDL_RenderFillRect(mSdlRenderer.get(), &rect);
    drawHighlights(rect, color);
}

void Renderer::drawHighlights(const SDL_Rect& rect, const RGBColor& color)
{
    auto x = rect.x;
    auto y = rect.y;
    auto w = rect.w;
    auto h = rect.h;

    setDrawColor(color.lighter());
    SDL_RenderDrawLine(mSdlRenderer.get(), x, y + h, x, y);
    SDL_RenderDrawLine(mSdlRenderer.get(), x + 1, y + h, x + 1, y);
    SDL_RenderDrawLine(mSdlRenderer.get(), x, y, x + w, y);
    SDL_RenderDrawLine(mSdlRenderer.get(), x, y + 1, x + w, y + 1);

    setDrawColor(color.darker());
    SDL_RenderDrawLine(mSdlRenderer.get(), x, y + h, x + w, y + h);
    SDL_RenderDrawLine(mSdlRenderer.get(), x, y + h - 1, x + w, y + h - 1);
    SDL_RenderDrawLine(mSdlRenderer.get(), x + w, y + h, x + w, y);    
    SDL_RenderDrawLine(mSdlRenderer.get(), x + w - 1, y + h, x + w - 1, y);
}

SDL_Rect Renderer::toSDLRect(const GameObject& obj) const
{
    SDL_Rect rect;
    rect.w = mWidthFactor * obj.width();
    rect.h = mHeightFactor * obj.height();
    auto p = obj.topLeft();
    rect.x = mWidthFactor * p.x;
    rect.y = mHeightFactor * p.y;
    return rect;
}

void Renderer::setDrawColor(const RGBColor& color)
{
    SDL_SetRenderDrawColor(mSdlRenderer.get(), color.r(), color.g(), color.b(),
                           color.a());
}

RGBColor Renderer::getBrickDrawColor(const Brick& brick)
{
    auto hp = brick.hitpoints();

    assert(hp >= 0 && hp <= 9);

    std::array<RGBColor, 9> colors{
        RGBColor{0xFD, 0xEF, 0x42}, RGBColor{0x99, 0xFF, 0x00},
        RGBColor{0x00, 0x7E, 0x56}, RGBColor{0x00, 0x5A, 0x7E},
        RGBColor{0x46, 0x3A, 0xCB}, RGBColor{0xF4, 0x0b, 0xEC},
        RGBColor{0xA4, 0x4E, 0xFE}, RGBColor{0xFF, 0x7B, 0x00},
        RGBColor{0xF4, 0x46, 0x11}};

    return RGBColor{colors.at(static_cast<std::size_t>(hp - 1))};
}
} // namespace bricks