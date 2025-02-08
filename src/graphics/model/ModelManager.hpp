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

    std::unordered_map<size_t, std::unique_ptr<BakedModel>> baked_models;
    std::unordered_map<size_t, std::unique_ptr<Model>> unbaked_models;

    std::unordered_map<size_t, std::unique_ptr<GLTexture>> gl_textures;
public:
    ModelManager(TextureManager* tex_manager) : texture_manager(tex_manager) {}

    //void loadAnimation(size_t model_loc, size_t anim_loc, const std::vector<size_t> &tex_locs, AnimSequence *anim_seq);
    void loadAnimator(size_t model_loc, SpriteAnimator *animator);

    BakedModel* getModel(size_t location);
    Model* getUnbakedModel(size_t location);

    void bakeModel(Model model, size_t model_location, size_t texture_location, size_t atlas_location);
    void createModel(size_t location, size_t texture_location, size_t atlas_location);
};

#endif