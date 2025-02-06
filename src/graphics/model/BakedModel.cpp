#include "../texture/Texture.hpp"
#include "BakedModel.hpp"

#define GL_TRIANGLES 4

//TextureAtlasPos* BakedModel::getAtlasPos() {
//    return atlas_pos;
//}

void BakedModel::updateInstance(const size_t &index) {
    InstanceModelData& instance = instances[index];
    if(instance.active == false) {
        instance.object_id = index;
        instance.active = true;
    } else if(instance.object_id != index) {
        instances.erase(instances.begin() + index);
    }

    mesh->updateInstanceBuffer(index, NULL, instance.data);
}

void BakedModel::updateInstances(const size_t &size) {
    if(size > mesh->instance_buffer_size) {
        mesh->instance_buffer_size*=2;
        mesh->updateInstanceBuffer();
        instances.resize(mesh->instance_buffer_size);
    } else if(size <= mesh->instance_buffer_size/2) {
        mesh->instance_buffer_size/=2;
        mesh->updateInstanceBuffer();
    }
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