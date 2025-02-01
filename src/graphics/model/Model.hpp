#ifndef VERTEXINFO_HPP
#define VERTEXINFO_HPP

#include <vector>
#include "VertexBuffer.hpp"

static unsigned int attrs[] = { 3,2,0 };

class ModelManager;

class Model {
protected:
    VertexBuffer vertexBufferData;

    friend class ModelManager;
public:
    Model() {};
};

#endif