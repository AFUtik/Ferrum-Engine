#include "../physics/RigidBody.hpp"
#include "../world/Entity.hpp"

#include "EntityRenderer.hpp"

#include "Shader.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "DrawContext.hpp"

#include "glm/glm.hpp"

void EntityRenderer::render(std::vector<Entity*> entities) { // Renders only registered entities//
    Mesh* mesh = new Mesh(PLANE, attrs);

    int index = 0;
    int id = 1;

    float uvsize = 1.0f / 16.0f;
	float u = (id % 16) * uvsize;
	float v = 1 - ((1 + id / 16) * uvsize);

    mesh->add_vertex(0 - 0.5f, 0 - 0.5f, 0, u, v);
	mesh->add_vertex(0 + 0.5f, 0 + 0.5f, 0, u + uvsize, v + uvsize);
	mesh->add_vertex(0 - 0.5f, 0 + 0.5f, 0, u, v + uvsize);
	mesh->add_vertex(0 - 0.5f, 0 - 0.5f, 0, u, v);
	mesh->add_vertex(0 + 0.5f, 0 - 0.5f, 0, u + uvsize, v);
	mesh->add_vertex(0 + 0.5f, 0 + 0.5f, 0, u + uvsize, v + uvsize);

    mesh->generate();
    meshes.push_back(mesh);
}

void EntityRenderer::draw(DrawContext* draw_context, std::vector<Entity*> &entities) {
    glm::mat4 model(1.0f);
    for(Entity* drawable : entities) {
        textures[drawable->texture_id]->bind();
        model = glm::translate(glm::mat4(1.0f), drawable->rigid_body->position);
        draw_context->shader->uniformMatrix("model", model);
    }
}