#include "ObjectRenderer.hpp"

#include "../Shader.hpp"
#include "../model/Mesh.hpp"
#include "../model/BakedModel.hpp"

void ObjectRenderer::render(Mesh* mesh, glm::mat4 &transform) {
    shader->uniformMatrix("model", transform);
    mesh->draw(4);
}

void ObjectRenderer::render(BakedModel* model, glm::mat4 &transform) {
    shader->uniformMatrix("model", transform);
    model->render();
}