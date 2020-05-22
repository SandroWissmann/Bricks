#ifndef BRICK_H
#define BRICK_H

#include "GameObject.h"

namespace bricks {

struct Hitpoints {
    int value;

    int operator()() const { return value; }
};

	class Brick : public GameObject
	{
	public:
        Brick(Point topLeft, Width width, Height height, Hitpoints hitpoints);
		~Brick() override = default;

        Brick (const Brick &) = default;
        Brick(Brick&&) = default;
        Brick& operator=(const Brick& other) = default;
        Brick& operator=(Brick&& other) = default;

        int startHitpoints() const;
        int hitpoints() const;

		void decreaseHitpoints();
		bool isDestroyed() const;
	private:
        const int mStartHitpoints;
        int mHitpoints;
	};
}  // namespace bricks
#endif
