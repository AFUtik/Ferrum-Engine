#ifndef ANIMSEQUENCE_HPP
#define ANIMSEQUENCE_HPP

#include <string>
#include <vector>

struct AnimationSequence {
    std::string name;
    std::vector<float> keyframes;

    uint32_t frames;
    float duration = 0.0f;
};

#endif