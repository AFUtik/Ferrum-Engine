#include "../texture/Texture.hpp"
#include "BakedModel.hpp"

#include <iostream>

#define GL_TRIANGLES 4

//TextureAtlasPos* BakedModel::getAtlasPos() {
//    return atlas_pos;
//}

void BakedModel::updateInstance(const size_t &index) {
    mesh->updateInstanceBuffer(index, NULL, model_instances[index].instance->data);
}

Mesh* BakedModel::getMesh() {
    return mesh.get();
};

void BakedModel::bindTexture() {
    texture->bind();
};

void BakedModel::render() {
    mesh->draw(render_mode);
};