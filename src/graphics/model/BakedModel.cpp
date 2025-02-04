#include "../texture/Texture.hpp"
#include "BakedModel.hpp"

#define GL_TRIANGLES 4

//TextureAtlasPos* BakedModel::getAtlasPos() {
//    return atlas_pos;
//}

Mesh* BakedModel::getMesh() {
    return mesh.get();
};

void BakedModel::bindTexture() {
    mesh_texture->bind();
};

void BakedModel::render() {
    mesh->draw(render_mode);
};