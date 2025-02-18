#ifndef MODELMANAGER_HPP
#define MODELMANAGER_HPP

#include <memory>

#include "../texture/TextureManager.hpp"
#include "../texture/GLTexture.hpp"
#include "BakedModel.hpp"
#include "Model.hpp"

class ModelManager {
private:
    TextureManager* texture_manager;

    std::unordered_map<std::string, std::unique_ptr<BakedModel>> baked_models;
    std::unordered_map<std::string, std::unique_ptr<Model>> unbaked_models;

    std::unordered_map<std::string, std::unique_ptr<GLTexture>> gl_textures;
public:
    ModelManager(TextureManager* tex_manager) : texture_manager(tex_manager) {}

    BakedModel* getModel(const std::string &location);
    Model* getUnbakedModel(const std::string &location);

    void bakeModel(Model model, std::string model_loc, std::string texture_loc, std::string tilemap_loc);
    void createModel(std::string model_loc, std::string texture_loc, std::string tilemap_loc);
};

#endif