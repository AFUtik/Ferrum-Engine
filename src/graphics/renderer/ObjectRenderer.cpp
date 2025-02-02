#include "ObjectRenderer.hpp"

#include "../Shader.hpp"
#include "../model/Mesh.hpp"
#include "../model/BakedModel.hpp"

void ObjectRenderer::render(Mesh* mesh) {
    mesh->draw(4);
}

void ObjectRenderer::render(BakedModel* model) {
    model->render();
}