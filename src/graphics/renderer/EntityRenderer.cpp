#include "EntityRenderer.hpp"

#include "../../game/entity/EntitySystem.hpp"

#include "../model/Mesh.hpp"
#include "../model/BakedModel.hpp"
#include "../model/ModelManager.hpp"


#include "../texture/Textures.hpp"
#include "../texture/Texture.hpp"

void EntityRenderer::render() {
    texture_m->getGLTexture(ALL_TEXTURES_ATLAS)->bind();
    
    for (auto&& [id, map] : entity_s->entity_map) {
        BakedModel* baked_model = model_m->getModel(id);
        int entity_count = map.size();

        int index = 0;
        if(entity_count != last_count) baked_model->updateInstances(entity_count);
        for (auto&& [ptr, unique_ptr] : map) {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), unique_ptr->getTransform());

            baked_model->updateInstance(index, model);
         
            index++;
            last_count = index;
        }
        object_renderer->render(baked_model);
    }
}