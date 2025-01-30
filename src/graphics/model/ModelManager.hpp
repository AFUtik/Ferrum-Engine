#ifndef MODELMANAGER_HPP
#define MODELMANAGER_HPP

#include <memory>

#include "../texture/TextureManager.hpp"
#include "BakedModel.hpp"
#include "Model.hpp"

class ModelManager {
private:
    TextureManager* texture_manager;
    std::unordered_map<size_t, std::unique_ptr<BakedModel>> baked_models;
public:
    ModelManager(TextureManager* tex_manager) : texture_manager(tex_manager) {}
    // virtual ~ModelManager();

    BakedModel* getModel(size_t location);

    //void bakeModel(Model model, size_t location, size_t texture_location);
    void bakeModel(Model model, size_t location, size_t texture_location, size_t atlas_location);
};

#endif