#include "../texture/Texture.hpp"
#include "BakedModel.hpp"

#define GL_TRIANGLES 4

//TextureAtlasPos* BakedModel::getAtlasPos() {
//    return atlas_pos;
//}

void BakedModel::updateInstance(const size_t &index) {
    InstanceModelData& instance = instances[index];
    if(instance.object_id != index) instances.erase(instances.begin() + index);

    mesh->updateInstanceBuffer(index, 0, instance.data);
}

void BakedModel::updateInstances(const size_t &size) {
    instances.resize(size);
    mesh->updateInstanceBuffer(size);
    mesh->instance_count = size;
}

Mesh* BakedModel::getMesh() {
    return mesh.get();
};

void BakedModel::bindTexture() {
    mesh_texture->bind();
};

void BakedModel::render() {
    mesh->draw(render_mode);
};