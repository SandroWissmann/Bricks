#ifndef RENDERER_H
#define RENDERER_H

#include "RGBColor.h"

#include "SDL_RAII.h"

#include <SDL.h>

#include <string>
#include <vector>

namespace bricks {

namespace game_objects {
class Ball;
class Platform;
class Wall;
class Brick;
class IndestructibleBrick;
class GameObject;
}

class Level;

class Renderer {
public:
    Renderer(const std::size_t screenWidth, const std::size_t screenHeight,
             const std::size_t gridWidth, const std::size_t gridHeight);
    ~Renderer();

    void render(const Level& level);

    void setWindowTitle(const std::string& title);

private:
    void clearScreen();
    void updateScreen();

    void render(const game_objects::Ball& ball);
    void render(const game_objects::Platform& platform);
    void render(const game_objects::Wall& wall);
    void render(const game_objects::Brick& brick);
    void render(const game_objects::IndestructibleBrick& indestructibleBrick);
    void render(const game_objects::GameObject& obj, const RGBColor& color);

    void drawHighlights(const SDL_Rect& rect, const RGBColor& color);

    SDL_Rect toSDLRect(const game_objects::GameObject& obj) const;
    void setDrawColor(const RGBColor& color);
    RGBColor getBrickDrawColor(const game_objects::Brick& brick);

    SDL_RAII mSDLRAII;
    SDL_Window* mSdlWindow;
    SDL_Renderer* mSdlRenderer;

    const std::size_t mScreenWidth;
    const std::size_t mScreenHeight;
    const std::size_t mGridWidth;
    const std::size_t mGridHeight;
    const double mWidthFactor;
    const double mHeightFactor;
};

} // namespace bricks

#endif