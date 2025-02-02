#include "../texture/Texture.hpp"
#include "Mesh.hpp"
#include "BakedModel.hpp"

#define GL_TRIANGLES 4

//TextureAtlasPos* BakedModel::getAtlasPos() {
//    return atlas_pos;
//}

Mesh* BakedModel::getMesh() {
    return mesh;
}

void BakedModel::clearInstances() {
    InstanceBuffer* instanceBuffer = mesh->getInstanceBuffer();
    instanceBuffer->mats.clear();
}

void BakedModel::updateInstances() {
    mesh->updateInstanceBuffer();
}

void BakedModel::updateInstance(int index, glm::mat4 &transform) {
    mesh->updateInstanceBuffer(index, transform);
}

void BakedModel::addInstance(glm::mat4 &transform) {
    InstanceBuffer* instanceBuffer = mesh->getInstanceBuffer();
    instanceBuffer->mats.push_back(transform);
};

void BakedModel::render() {
    mesh->draw(GL_TRIANGLES);
};

BakedModel::~BakedModel() {
    delete mesh;
};