#include "../texture/TextureManager.hpp"
#include "ModelManager.hpp"
#include "Mesh.hpp"

void ModelManager::bakeModel(Model model, size_t location, size_t texture_location) {
    GLTexture* gl_texture = texture_manager->getGLTexture(texture_location);
    Mesh* mesh = new Mesh(model.vertexBufferData);

    baked_models[location] = std::make_unique<BakedModel>(mesh, gl_texture);
}

BakedModel* ModelManager::getModel(size_t location) {
    return baked_models[location].get();
}