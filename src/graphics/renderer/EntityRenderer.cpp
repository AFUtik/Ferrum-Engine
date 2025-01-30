#include "EntityRenderer.hpp"

#include "../../entity/EntitySystem.hpp"

#include "../model/Mesh.hpp"
#include "../model/BakedModel.hpp"
#include "../model/ModelManager.hpp"

#include "../texture/Texture.hpp"

#include "../Shader.hpp"

void EntityRenderer::render(Shader* shader) {
    texture_m->getGLTexture(3)->bind();
    glm::mat4 model(1.0f);
    for(auto&& [id, map] : entity_s->entity_map) {
        BakedModel* baked_model = model_m->getModel(id);
        for(auto&& [ptr, unique_ptr] : map) {
            model = glm::translate(glm::mat4(1.0f), unique_ptr->getTransform());
            shader->uniformMatrix("model", model);
            baked_model->render();
        }
    }
}