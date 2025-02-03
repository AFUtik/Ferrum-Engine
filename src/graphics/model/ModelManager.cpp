#include "../texture/TextureManager.hpp"
#include "../texture/TextureAtlasPos.hpp"

#include "ModelManager.hpp"
#include "Mesh.hpp"

void ModelManager::bakeModel(Model model, size_t location, size_t texture_location, size_t atlas_location) {
    Mesh* mesh = new Mesh(model.vertexBufferData);
    TextureAtlasPos* texture_pos = texture_manager->getAtlas(atlas_location)->getAtlasPos(texture_location);
    mesh->setUV(texture_pos->u1, texture_pos->u2, texture_pos->v1, texture_pos->v2);
    mesh->generate();
    baked_models[location] = std::make_unique<BakedModel>(mesh);
}

void ModelManager::createModel(size_t location, size_t texture_location, size_t atlas_location) {
    TextureAtlasPos* texture_pos = texture_manager->getAtlas(atlas_location)->getAtlasPos(texture_location);
    Model* model = new Model();
    model->tex_atlas_pos = texture_pos;
    model->vertexBufferData = nullptr;
    unbaked_models[location] = std::unique_ptr<Model>(model);
}

BakedModel* ModelManager::getModel(size_t location) {
    return baked_models[location].get();
}

Model* ModelManager::getUnbakedModel(size_t location) {
    return unbaked_models[location].get();
}