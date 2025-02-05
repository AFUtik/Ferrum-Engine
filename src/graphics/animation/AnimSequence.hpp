#ifndef ANIMSEQUENCE_HPP
#define ANIMSEQUENCE_HPP

#include <string>
#include <vector>

class AnimSequence {
private:
    std::string seq_name;

    std::vector<float> keyframes;
    unsigned int frames;
    bool interpolate;
    bool reset;

    unsigned int curr_frame;
    float curr_time_ms;
    float total_time;
public:
    AnimSequence();
    ~AnimSequence();

    unsigned int animate(float delta_time);
};

#endif