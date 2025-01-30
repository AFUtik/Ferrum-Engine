#include "../texture/Texture.hpp"
#include "Mesh.hpp"
#include "BakedModel.hpp"

#define GL_TRIANGLES 4

//TextureAtlasPos* BakedModel::getAtlasPos() {
//    return atlas_pos;
//}

void BakedModel::render() {
    mesh->draw(GL_TRIANGLES);
};

BakedModel::~BakedModel() {
    delete mesh;
};