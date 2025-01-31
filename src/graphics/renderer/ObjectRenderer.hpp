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

public:
    ObjectRenderer(Shader* shader) : shader(shader) {};

    void render(Mesh* mesh, glm::mat4 &transform);
    void render(BakedModel* model, glm::mat4 &transform);
};

#endif