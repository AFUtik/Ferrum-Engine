#include "SpriteAnimator.hpp"
#include "../texture/TextureAtlas.hpp"

#include <iostream>

SpriteAnimator::SpriteAnimator(Tilemap* tilemap) {
    size_t tiles = tilemap->getTilesAmount();
    offsets.push_back(0);
}

void SpriteAnimator::loadAnimSequence(AnimSequence* sequence, size_t texture_location) {
    anim_seq.push_back(std::unique_ptr<AnimSequence>(sequence));
    TextureAtlasPos* first
}

TextureAtlasPos* SpriteAnimator::animate(const size_t &anim, unsigned int &current_frame, float &delta_time) {
    AnimSequence* sequence = anim_seq[anim].get();
    const unsigned int& offset = offsets[anim];
    const float& next_keyframe = sequence->keyframes[current_frame+1];
    if(delta_time > next_keyframe) current_frame++;
    
    if(current_frame+1 > sequence->frames) {
        current_frame = 0;
        delta_time = 0.0f;
    }
    return sprites_pos[current_frame + offset];
}