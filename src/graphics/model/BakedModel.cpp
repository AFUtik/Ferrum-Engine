#include "../texture/Texture.hpp"
#include "Mesh.hpp"
#include "BakedModel.hpp"

#define GL_TRIANGLES 4

//TextureAtlasPos* BakedModel::getAtlasPos() {
//    return atlas_pos;
//}

void BakedModel::clearInstances() {
    InstanceBuffer* instanceBuffer = mesh->getInstanceBuffer();
    instanceBuffer->mats.clear();
}

void BakedModel::updateInstances(int size) {
    InstanceBuffer* instanceBuffer = mesh->getInstanceBuffer();
    instanceBuffer->mats.resize(size);
    mesh->updateInstanceBuffer();
}

void BakedModel::updateInstance(int index, glm::mat4 &transform) {
    mesh->updateInstanceBuffer(index, transform);
}

void BakedModel::render() {
    mesh->draw(GL_TRIANGLES);
};

BakedModel::~BakedModel() {
    delete mesh;
};