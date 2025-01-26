#include "../texture/TextureManager.hpp"
#include "ModelManager.hpp"
#include "Model.hpp"
#include "Mesh.hpp"

int attrs[] = { 3,2,0 };

void ModelManager::bakeModel(Model model, size_t location, size_t texture_location) {
    Texture* texture = texture_manager->getTexture(texture_location);
    Mesh* mesh = new Mesh(model.vertex_size/5, attrs);
    std::vector<float> &vertex = model.vertex_info;
    for(int i = 0; i < model.vertex_size; i+=5) {
        mesh->add_vertex(vertex[i], vertex[i+1], vertex[i+2], vertex[i+3], vertex[i+4]);
    }
    mesh->generate();
    baked_models[location] = std::make_unique<BakedModel>(mesh, texture);
}

BakedModel* ModelManager::getModel(size_t location) {
    return baked_models[location].get();
}