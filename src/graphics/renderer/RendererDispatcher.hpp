#ifndef OBJECTRENDERERDISPATCHER_HPP
#define OBJECTRENDERERDISPATCHER_HPP

class Shader;
class GLTexture;
class TextureManager;
class ModelManager;
class BakedModel;

#include "glm/glm.hpp"

class ObjectRendererDispatcher {
protected:
    TextureManager* texture_m;
    ModelManager* model_m;
public:
    ObjectRenderer(TextureManager* textureManager, ModelManager* modelManager) : texture_m(textureManager), model_m(modelManager) {};

    virtual void renderObject(BakedModel* model, glm::mat4 &model_mat) = 0;

    void useAtlas(size_t location) const;
};

#endif