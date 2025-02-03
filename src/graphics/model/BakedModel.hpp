#ifndef BAKEDMODEL_HPP
#define BAKEDMODEL_HPP

class Mesh;
class GLTexture;
class TextureAtlasPos;

#include "glm/glm.hpp"

class BakedModel {
protected:
    //GLTexture* gl_texture;
    Mesh* mesh;

    friend class ModelManager;
public:
    BakedModel(Mesh* mesh) : mesh(mesh) {};
    ~BakedModel();

    Mesh* getMesh();
    void render();
};

#endif