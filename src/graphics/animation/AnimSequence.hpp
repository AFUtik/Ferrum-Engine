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

    float duration;

    friend class SpriteAnimator;
public:
    AnimSequence(std::string name, unsigned int frames, const std::vector<float> &keyframes) : seq_name(name), frames(frames), keyframes(keyframes) {};
    //~AnimSequence();
};

#endif