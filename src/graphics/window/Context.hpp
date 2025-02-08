#ifndef CONTEXT_HPP
#define CONTEXT_HPP

struct Context {
    float delta_time = 0;
    float last_ticks = 0;
    float time_accu = 0;
};

#endif