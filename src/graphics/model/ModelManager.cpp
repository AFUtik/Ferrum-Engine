#include "../texture/TextureManager.hpp"
#include "../texture/TextureRegion.hpp"
#include "../texture/TextureGLHandler.hpp"

#include "ModelManager.hpp"

#include <iostream>

void ModelManager::loadAnimator(std::string model_loc, SpriteAnimator *animator) {
    BakedModel* baked_model = baked_models[model_loc].get();
    if(baked_model==nullptr) {
        std::cerr << "The baked model not found - " << model_loc << std::endl;
    }
    baked_model->animator = std::unique_ptr<SpriteAnimator>(animator);
}

void ModelManager::bakeModel(Model model, std::string model_loc, std::string texture_loc, std::string tilemap_loc) {
    Tilemap* tilemap = texture_manager->getTilemap(tilemap_loc);
    if(tilemap==nullptr) {
        std::cerr << "ModelManager: atlas not found - " << tilemap_loc << std::endl;
        return;
    }
    TextureRegion* texture_reg = tilemap->getTextureRegion(texture_loc);
    if(texture_reg==nullptr) {
        std::cerr << "ModelManager: texture position not found - " << texture_reg << std::endl;
        return;
    }
    BakedModel* baked_model = new BakedModel(nullptr);
    Mesh* mesh = new Mesh(model.vertexBufferData);
    mesh->setUV(texture_reg->u1, texture_reg->u2, texture_reg->v1, texture_reg->v2);
    mesh->generate();

    GLTexture* gl_texture = gl_textures[tilemap_loc].get();
    if(gl_texture==nullptr) {
        GLTexture *gl_new_texture = TextureGLHandler::createTexture(tilemap->getAtlasTexture());
        gl_textures[tilemap_loc] = std::unique_ptr<GLTexture>(gl_new_texture);
        gl_texture = gl_new_texture;
    }

    baked_model->mesh = std::unique_ptr<Mesh>(mesh);
    baked_model->texture = gl_texture;
    baked_model->tilemap = tilemap;
    baked_model->texture_reg = texture_reg;
    baked_models[model_loc] = std::unique_ptr<BakedModel>(baked_model);
}

void ModelManager::createModel(std::string model_loc, std::string texture_loc, std::string tilemap_loc) {
    Tilemap* atlas = texture_manager->getTilemap(texture_loc);
    if(atlas==nullptr) {
        std::cerr << "ModelManager: atlas not found - " << texture_loc << std::endl;
        return;
    }
    TextureRegion* texture_reg = atlas->getTextureRegion(texture_loc);
    if(texture_reg==nullptr) {
        std::cerr << "ModelManager: texture position not found - " << texture_loc << std::endl;
        return;
    }

    Model* model = new Model();
    model->texture_reg = texture_reg;
    model->vertexBufferData = nullptr;
    unbaked_models[model_loc] = std::unique_ptr<Model>(model);
}

BakedModel* ModelManager::getModel(const std::string &location) {
    return baked_models[location].get();
}

Model* ModelManager::getUnbakedModel(const std::string &location) {
    return unbaked_models[location].get();
}