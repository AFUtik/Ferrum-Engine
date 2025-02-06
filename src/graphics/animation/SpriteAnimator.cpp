#include "SpriteAnimator.hpp"

TextureAtlasPos* SpriteAnimator::animate(const size_t &anim, unsigned int &current_frame, float delta_time) {
    AnimSequence* sequence = anim_seq[anim].get();
    if(current_frame+1 >= sequence->frames) current_frame = 0;

    const unsigned int& offset = offsets[anim];
    const float& next_keyframe = sequence->keyframes[current_frame+1];
    if(delta_time > next_keyframe) current_frame++;

    return sprites_pos[current_frame + offset];
}