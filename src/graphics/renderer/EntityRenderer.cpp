#include "EntityRenderer.hpp"

#include "../../entity/EntitySystem.hpp"

#include "../model/Mesh.hpp"
#include "../model/BakedModel.hpp"
#include "../model/ModelManager.hpp"

#include "../texture/Texture.hpp"

#include "../Shader.hpp"

EntityRenderer::EntityRenderer(ModelManager* model_m, EntitySystem* entity_s) : model_m(model_m), entity_s(entity_s) {

}

void EntityRenderer::render(Shader* shader) {
    glm::mat4 model(1.0f);
    for(auto&& [id, map] : entity_s->entity_map) {
        BakedModel* baked_model = model_m->getModel(id);
        baked_model->getTexture()->bind();
        for(auto&& [ptr, unique_ptr] : map) {
            model = glm::translate(glm::mat4(1.0f), unique_ptr->getTransform());
            shader->uniformMatrix("model", model);
            baked_model->render();
        }
    }
}