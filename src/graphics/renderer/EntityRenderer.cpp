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
    for(auto&& [id, map] : entity_s->entity_map) {
        BakedModel* baked_model = model_m->getModel(id);
        for(auto&& [ptr, unique_ptr] : map) {
            model = glm::translate(glm::mat4(1.0f), unique_ptr->getTransform());
            object_renderer->render(baked_model, model);
        }
    }
}