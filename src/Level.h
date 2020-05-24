#ifndef LEVEL_H
#define LEVEL_H

#include "Brick.h"
#include "IndestructibleBrick.h"

#include <iosfwd>
#include <vector>

namespace bricks {

    struct Level {
        std::vector<Brick> bricks;
        std::vector<IndestructibleBrick> indestructibleBricks;
    };

    Level readFromFile(const std::string& filename);

    std::istream &operator>>(std::istream &is, Level &obj);

    namespace impl {
        bool isComment(const std::string line);
    }
}

#endif // LEVEL_H