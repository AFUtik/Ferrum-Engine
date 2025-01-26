#ifndef ENTITYMODEL_HPP
#define ENTITYMODEL_HPP

#include "Model.hpp"

static std::vector<float> vertices = {
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
};

class EntityModel : public Model {
public:
    EntityModel() : Model(vertices) {};
};

#endif