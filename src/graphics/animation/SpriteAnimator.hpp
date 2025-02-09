#ifndef SPRITEANIMATOR_HPP
#define SPRITEANIMATOR_HPP

#include "AnimSequence.hpp"
#include <memory>

struct TextureRegion;
class Tilemap;

class SpriteAnimator {
private:
    std::vector<std::unique_ptr<AnimSequence>> anim_seq;
    std::vector<size_t> offsets;
    
    Tilemap* tilemap;
public:
    SpriteAnimator(Tilemap* tilemap);

    AnimSequence* getAnimSequence(const size_t &sequence_id);
    void loadAnimSequence(AnimSequence* sequence, std::string texture_location);

    TextureRegion* animateSequence(const size_t &sequence_id, unsigned int &current_frame, float &delta_time);
};

#endif