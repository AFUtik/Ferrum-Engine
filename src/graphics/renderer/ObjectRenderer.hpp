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
    TextureManager* texture_manager;
    ModelManager* model_manager;

    unsigned int primitive;

    friend class DrawContext;
public:
    ObjectRenderer() : texture_manager(nullptr), model_manager(nullptr) {};

    ObjectRenderer(TextureManager* texture_m, ModelManager* model_m) : texture_manager(texture_m), model_manager(model_m) {};

    virtual void render();
};

#endif