#include "ObjectRenderer.hpp"

#include "../Shader.hpp"
#include "../model/Mesh.hpp"
#include "../model/BakedModel.hpp"

void ObjectRenderer::render(Mesh* mesh) {
    mesh->draw(4);
}