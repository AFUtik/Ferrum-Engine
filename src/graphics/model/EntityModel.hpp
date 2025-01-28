#ifndef ENTITYMODEL_HPP
#define ENTITYMODEL_HPP

#include "Model.hpp"

static float vertices[] = {
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
};

class EntityModel : public Model {
public:
    EntityModel() : Model() {
		vertexBufferData.vertices_list = vertices;
		vertexBufferData.vertex_size = 5;
		vertexBufferData.list_size = 6;
		vertexBufferData.attributes_list = attrs;
		vertexBufferData.attributes_list_size = 3;
	};
};

#endif