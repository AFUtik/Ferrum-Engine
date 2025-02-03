#include "EntityRenderer.hpp"

#include "../../game/entity/EntitySystem.hpp"

#include "../model/Mesh.hpp"
#include "../model/BakedModel.hpp"
#include "../model/ModelManager.hpp"


#include "../texture/Textures.hpp"
#include "../texture/Texture.hpp"

#include <iostream>

void EntityRenderer::render() {
    texture_m->getGLTexture(ALL_TEXTURES_ATLAS)->bind();
    for (auto&& [id, map] : entity_s->entity_map) {
        Mesh* mesh = model_m->getModel(id)->getMesh();
        size_t entity_count = map.size();
        unsigned int& instanced_amount = mesh->getInstancesAmount();

        int index = 0;
        if(entity_count != instanced_amount) mesh->updateInstanceBuffer(entity_count);
        for (auto&& [ptr, unique_ptr] : map) {
            Matrix4x4ArrayUtils::setPosition(instance_data, unique_ptr->getTransform());
            for(int i = 0; i < 2; i++) instance_data[16+i] = 0.0f;
            mesh->updateInstanceBuffer(index, instance_data);
            index++;
        }
        instanced_amount = index;
        object_renderer->render(mesh);
    }
}