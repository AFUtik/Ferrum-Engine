#include "../texture/TextureManager.hpp"
#include "../texture/TextureAtlasPos.hpp"

#include "ModelManager.hpp"

#include <iostream>

void ModelManager::bakeModel(Model model, size_t location, size_t texture_location, size_t atlas_location) {
    TextureAtlas* atlas = texture_manager->getAtlas(atlas_location);
    if(atlas==nullptr) {
        std::cerr << "ModelManager: atlas not found - " << atlas_location << std::endl;
        return;
    }
    TextureAtlasPos* texture_pos = atlas->getAtlasPos(texture_location);
    if(texture_pos==nullptr) {
        std::cerr << "ModelManager: texture position not found - " << texture_location << std::endl;
        return;
    }
    BakedModel* baked_model = new BakedModel(nullptr);
    Mesh* mesh = new Mesh(model.vertexBufferData);
    mesh->setUV(texture_pos->u1, texture_pos->u2, texture_pos->v1, texture_pos->v2);
    mesh->generate();

    baked_model->mesh = std::unique_ptr<Mesh>(mesh);
    baked_model->atlas = atlas;
    baked_model->atlas_pos = texture_pos;
    baked_models[location] = std::unique_ptr<BakedModel>(baked_model);
}

void ModelManager::createModel(size_t location, size_t texture_location, size_t atlas_location) {
    TextureAtlas* atlas = texture_manager->getAtlas(atlas_location);
    if(atlas==nullptr) {
        std::cerr << "ModelManager: atlas not found - " << atlas_location << std::endl;
        return;
    }
    TextureAtlasPos* texture_pos = atlas->getAtlasPos(texture_location);
    if(texture_pos==nullptr) {
        std::cerr << "ModelManager: texture position not found - " << texture_location << std::endl;
        return;
    }

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