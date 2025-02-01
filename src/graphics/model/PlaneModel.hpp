#ifndef ENTITYMODEL_HPP
#define ENTITYMODEL_HPP

#include "Model.hpp"

static float vertices[] = {
	 -0.5f,  -0.5f, 0.0f, 0.0f, 0.0f,
	 -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
	 0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,
};

static unsigned int indices[] = {
    0, 1, 3,
	1, 2, 3
};


class PlaneModel : public Model {
public:
    PlaneModel() : Model() {
		vertexBufferData->vertices_list = vertices;
		vertexBufferData->vertex_size = 5;
		vertexBufferData->list_size = 4;
		
		vertexBufferData->attributes_list = attrs;
		vertexBufferData->attributes_list_size = 3;

		vertexBufferData->indices_list = indices;
		vertexBufferData->indices_list_size = 6;
	};
};

#endif