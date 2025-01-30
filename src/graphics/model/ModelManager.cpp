#include "../texture/TextureManager.hpp"
#include "../texture/TextureAtlasPos.hpp"

#include "ModelManager.hpp"
#include "Mesh.hpp"


#include <iostream>

void ModelManager::bakeModel(Model model, size_t location, size_t texture_location, size_t atlas_location) {
    TextureAtlasPos* texture_pos = texture_manager->getAtlas(atlas_location)->getAtlasPos(texture_location);
    std::cout << texture_pos->u1 << " " << texture_pos->u2 << " " << texture_pos->v1 << " " << texture_pos->v2 << std::endl;
    
    Mesh* mesh = new Mesh(model.vertexBufferData);
    mesh->setUV(texture_pos->u1, texture_pos->u2, texture_pos->v1, texture_pos->v2);
    mesh->generate();
    baked_models[location] = std::make_unique<BakedModel>(mesh);
}

BakedModel* ModelManager::getModel(size_t location) {
    return baked_models[location].get();
}