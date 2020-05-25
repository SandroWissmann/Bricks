#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>

#include <vector>

class Ball;
class Platform;
class Wall;
class Level;

namespace bricks {

class Renderer {
public:
    Renderer(const std::size_t screenWidth, const std::size_t screenHeight,
             const std::size_t gridWidth, const std::size_t gridHeight);
    ~Renderer();

    void Render(const Ball &ball, const Platform &platform, const Level &level);

private:
    SDL_Window *mSdlWindow;
    SDL_Renderer *mSdlRenderer;

    const std::size_t mScreenWidth;
    const std::size_t mScreenHeight;
    const std::size_t mGridWidth;
    const std::size_t mGridHeight;
};

} // namespace bricks

#endif