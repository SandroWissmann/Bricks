#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>

#include <vector>

namespace bricks {

class Ball;
class Platform;
class Wall;
class Level;
class Brick;
class IndestructibleBrick;
class GameObject;

class Renderer {
public:
    Renderer(const std::size_t screenWidth, const std::size_t screenHeight,
             const std::size_t gridWidth, const std::size_t gridHeight);
    ~Renderer();

    void render(const Ball &ball, const Platform &platform, const Level &level);
private:
    void clearScreen();
    void updateScreen();

    void render(const Ball &ball);
    void render(const Platform &platform);
    void render(const Brick& brick);
    void render(const IndestructibleBrick& indestructibleBrick);

    SDL_Rect toSDLRect(const GameObject& obj) const;

    SDL_Window *mSdlWindow;
    SDL_Renderer *mSdlRenderer;

    const std::size_t mScreenWidth;
    const std::size_t mScreenHeight;
    const std::size_t mGridWidth;
    const std::size_t mGridHeight;
    const double mWidthFactor;
    const double mHeightFactor;
};

} // namespace bricks

#endif