#ifndef GETEVENT_H
#define GETEVENT_H

namespace bricks {

enum class Event { none, quit, left, right, space, escape, p };

Event getEvent();
} // namespace bricks

#endif