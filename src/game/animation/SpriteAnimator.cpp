#include "SpriteAnimator.hpp"

#include "../../utils/tilemap/Tilemap.hpp"

#include <iostream>

SpriteAnimator::SpriteAnimator(Tilemap* tilemap) : tilemap(tilemap) {

}

void SpriteAnimator::loadAnimSequence(AnimationSequence* sequence, std::string texture_location) {
    anim_seq.push_back(std::unique_ptr<AnimationSequence>(sequence));
    
    offsets.push_back(tilemap->getTextureRegionPos(texture_location));
}

TextureRegion* SpriteAnimator::animateSequence(const size_t &anim, unsigned int &current_frame, float &delta_time) {
    AnimationSequence* sequence = anim_seq[anim].get();
    const size_t& offset = offsets[anim];
    const float& next_keyframe = sequence->keyframes[current_frame+1];
    if(delta_time > next_keyframe) current_frame++;
    
    if(current_frame+1 > sequence->frames) {
        current_frame = 0;
        delta_time = 0.0f;
    }
    return tilemap->getTextureRegion(current_frame + offset);
}