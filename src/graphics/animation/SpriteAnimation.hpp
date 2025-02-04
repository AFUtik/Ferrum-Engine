#ifndef SPRITEANIMATION_HPP
#define SPRITEANIMATION_HPP

#include "AnimSequence.hpp"

#include <memory>

class TextureAtlasPos;

class SpriteAnimation {
private:
    size_t animation_location;
    std::unique_ptr<AnimSequence> anim_seq;
    std::vector<TextureAtlasPos*> sprites_pos;
public:
    TextureAtlasPos* animate(float delta_time);
};

#endif