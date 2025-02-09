#ifndef VERTEXINFO_HPP
#define VERTEXINFO_HPP

#include "VertexBuffer.hpp"
#include "VertexInfo.hpp"

class ModelManager;
class TextureRegion;

class Model {
protected:
    VertexBuffer *vertexBufferData;
    TextureRegion* texture_reg;

    friend class ModelManager;
public:
    Model() {};

    inline TextureRegion* getTextureRegion() {return texture_reg;};
};

#endif