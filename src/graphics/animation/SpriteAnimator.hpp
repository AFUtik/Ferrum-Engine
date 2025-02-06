#ifndef SPRITEANIMATOR_HPP
#define SPRITEANIMATOR_HPP

#include "AnimSequence.hpp"
#include <memory>

class TextureAtlasPos;

class SpriteAnimator {
private:
    std::vector<std::unique_ptr<AnimSequence>> anim_seq;
    std::vector<TextureAtlasPos*> sprites_pos;
    
    std::vector<unsigned int> offsets;
public:
    void loadAnimSequence(AnimSequence* sequence, std::vector<TextureAtlasPos*> sprites_pos);

    TextureAtlasPos* animate(const size_t &sequence_id, unsigned int &current_frame, float delta_time);

    AnimSequence* getAnimSequence(const size_t &sequence_id);
};

#endif