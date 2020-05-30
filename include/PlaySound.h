#ifndef OPERATORDEGREE_H
#define OPERATORDEGREE_H

#include <string>

namespace bricks{

    void playSoundDestroyBrick();
    void playSoundHitBrick();
    void playSoundHitPlattform();

    void playSound(const std::string& filename);
}

#endif