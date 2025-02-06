#include "EntityRenderer.hpp"

#include "../../game/entity/EntitySystem.hpp"

#include "../model/BakedModel.hpp"
#include "../model/ModelManager.hpp"


#include "../texture/Textures.hpp"

#include <iostream>

void EntityRenderer::render() {
    for (auto&& [id, map] : entity_s->entity_map) {
        BakedModel* baked_model = model_m->getModel(id);
        SpriteAnimator* animator = baked_model->getSpriteAnimator();

        unsigned int& instanced_amount = baked_model->getInstancesAmount();
        size_t entity_count = map.size();

        int index = 0;
        //if(entity_count != instanced_amount) baked_model->updateInstances(entity_count);
        for (auto&& [ptr, unique_ptr] : map) {
            InstanceModelData& instance_model = baked_model->getInstanceModelData();

            Matrix4x4ArrayUtils::setPosition(instance_model.data, unique_ptr->getTransform());
            TextureAtlasPos* texture_pos = animator->animate(TEST_ANIMATION, instance_model.current_state, instance_model.animation_time);

            // assigning texture coordinates //
            instance_model.data[16] = texture_pos->u1;
            instance_model.data[17] = texture_pos->v1;

            baked_model->updateInstance(index);
        }
        instanced_amount = index;
        baked_model->bindTexture();
        baked_model->render();
    }
}