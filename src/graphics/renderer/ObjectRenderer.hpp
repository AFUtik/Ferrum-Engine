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
    GLTexture* basic_atlas;
    Shader* shader;

    unsigned int primitive;
public:
    ObjectRenderer(Shader* shader) : shader(shader) {};

    void render(Mesh* mesh);
    void render(BakedModel* model);
};

#endif