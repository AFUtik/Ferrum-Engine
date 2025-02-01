#ifndef VERTEXINFO_HPP
#define VERTEXINFO_HPP

#include "VertexBuffer.hpp"
#include "VertexInfo.hpp"

class ModelManager;
class TextureAtlasPos;

class Model {
protected:
    VertexBuffer *vertexBufferData;
    TextureAtlasPos* tex_atlas_pos;

    friend class ModelManager;
public:
    Model() {};

    inline TextureAtlasPos* getUVPos() {return tex_atlas_pos;};
};

#endif