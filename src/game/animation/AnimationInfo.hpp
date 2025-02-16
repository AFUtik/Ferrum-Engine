#ifndef ANIMATIONINFO_HPP
#define ANIMATIONINFO_HPP

#include <cstdint>

struct AnimationInfo {
    uint32_t curr_seq;
    uint32_t curr_frame;
    float playing = 0.0f;
};

#endif