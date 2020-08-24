#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>

#include <memory>
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
} // namespace game_objects

namespace types {
class RGBColor;
}

class Level;

struct SDLWindowDeleter {
    void operator()(SDL_Window* window)
    {
        SDL_DestroyWindow(window);
    }
};

struct SDLRendererDeleter {
    void operator()(SDL_Renderer* renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
};

class Renderer {
public:
    Renderer(const std::size_t screenWidth, const std::size_t screenHeight,
             const std::size_t gridWidth, const std::size_t gridHeight);
    ~Renderer() = default;

    Renderer(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer& operator=(Renderer&&) = delete;

    void render(const Level& level);

    void setWindowTitle(const std::string& title);

    void setPaused(bool paused);

private:
    void clearScreen();
    void updateScreen();

    void render(const game_objects::Ball& ball);
    void render(const game_objects::Platform& platform);
    void render(const game_objects::Wall& wall);
    void render(const game_objects::Brick& brick);
    void render(const game_objects::IndestructibleBrick& indestructibleBrick);
    void render(const game_objects::GameObject& obj, types::RGBColor color);

    void drawHighlights(const SDL_Rect& rect, const types::RGBColor& color);

    SDL_Rect toSDLRect(const game_objects::GameObject& obj) const;
    void setDrawColor(const types::RGBColor& color);
    static types::RGBColor getBrickDrawColor(const game_objects::Brick& brick);

    std::unique_ptr<SDL_Window, SDLWindowDeleter> mSdlWindow;
    std::unique_ptr<SDL_Renderer, SDLRendererDeleter> mSdlRenderer;

    const std::size_t mScreenWidth;
    const std::size_t mScreenHeight;
    const std::size_t mGridWidth;
    const std::size_t mGridHeight;
    const double mWidthFactor;
    const double mHeightFactor;
    bool mPaused{false};
};

} // namespace bricks

#endif