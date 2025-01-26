#include "../texture/Texture.hpp"
#include "Mesh.hpp"
#include "BakedModel.hpp"

#define GL_TRIANGLES 4

Texture* BakedModel::getTexture() {
    return texture;
}

void BakedModel::render() {
    mesh->draw(GL_TRIANGLES);
};

BakedModel::~BakedModel() {
    delete mesh;
};