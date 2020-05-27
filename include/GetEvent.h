#ifndef GETEVENT_H
#define GETEVENT_H

namespace bricks{

    enum class Event{
        none,
        quit,
        left,
        right,
        space,
        escape
    };

    Event getEvent();
}

#endif