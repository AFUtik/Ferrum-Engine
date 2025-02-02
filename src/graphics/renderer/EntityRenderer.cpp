#include "EntityRenderer.hpp"

#include "../../game/entity/EntitySystem.hpp"

#include "../model/Mesh.hpp"
#include "../model/BakedModel.hpp"
#include "../model/ModelManager.hpp"


#include "../texture/Textures.hpp"
#include "../texture/Texture.hpp"

void EntityRenderer::render() {
    texture_m->getGLTexture(ALL_TEXTURES_ATLAS)->bind();
    glm::mat4 model(1.0f);
    int objects = 1;
    bool changed = false;
    BakedModel* baked_model = model_m->getModel(0);


    for(auto&& [id, map] : entity_s->entity_map) {
        //baked_model->clearInstances();
        int index = 0;
        for(auto&& [ptr, unique_ptr] : map) {
            InstanceBuffer* inBuffer = baked_model->getMesh()->getInstanceBuffer();
            if(inBuffer->mats.size() <= index) {
                inBuffer->mats.push_back(model);
                baked_model->updateInstances();
            }
            glm::mat4 model = glm::translate(glm::mat4(1.0f), unique_ptr->getTransform());
            baked_model->updateInstance(index, model);
            index++;
        }
        object_renderer->render(baked_model);
    }
}