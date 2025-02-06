#ifndef OBJECTRENDERER_HPP
#define OBJECTRENDERER_HPP

class Mesh;
class BakedModel;
class Shader;
class GLTexture;
class TextureManager;
class ModelManager;

#include "glm/glm.hpp"

class ObjectRenderer {
protected:
    Shader* shader;

    unsigned int primitive;
public:
    GLTexture* current_binded_texture;
    ObjectRenderer(Shader* shader) : shader(shader) {};

    void render(Mesh* mesh);
};

#endif