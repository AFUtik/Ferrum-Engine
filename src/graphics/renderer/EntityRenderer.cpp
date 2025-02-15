#include "EntityRenderer.hpp"

#include "../../game/entity/EntitySystem.hpp"

#include "../model/BakedModel.hpp"
#include "../model/ModelManager.hpp"

#include <iostream>

void EntityRenderer::render() {
    for (auto&& [tag, map] : entity_s->entity_map) {
        BakedModel* baked_model = model_manager->getModel(tag);
        SpriteAnimator* animator = baked_model->getSpriteAnimator();
        size_t entity_count = map.size();

        int index = 0;
        if(entity_count != baked_model->getInstancesAmount()) baked_model->updateInstances(entity_count);
        for (auto&& [ptr, unique_ptr] : map) {
            InstanceModelData& instance_model = baked_model->getInstanceModelData(index);
            instance_model.animation_time = ptr->anim_time;

            Matrix4x4ArrayUtils::setPosition(instance_model.data, unique_ptr->getTransform());
            if(animator != nullptr) {
                TextureRegion* texture_pos = animator->animateSequence(TEST_ANIMATION, instance_model.current_state, ptr->anim_time);

                // assigning texture coordinates //
                instance_model.data[16] = texture_pos->orig_u1;
                instance_model.data[17] = texture_pos->orig_v1;
            }
            baked_model->updateInstance(index);
            index++;
        }
        baked_model->bindTexture();
        baked_model->render();
    }
}