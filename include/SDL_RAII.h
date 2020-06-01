#ifndef SDL_RAII_H
#define SDL_RAII_H

namespace bricks {

class SDL_RAII {
public:
    static void init();

private:
    SDL_RAII();
    ~SDL_RAII() noexcept;

    SDL_RAII(const SDL_RAII&) = delete;
    SDL_RAII(SDL_RAII&&) = delete;
    SDL_RAII& operator=(const SDL_RAII&) = delete;
    SDL_RAII& operator=(SDL_RAII&&) = delete;
};

} // namespace bricks
#endif