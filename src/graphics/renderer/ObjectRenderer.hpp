#ifndef OBJECTRENDERER_HPP
#define OBJECTRENDERER_HPP

class Shader;
class GLTexture;
class TextureManager;
class ModelManager;

class ObjectRenderer {
protected:
    GLTexture* atlas;

    TextureManager* texture_m;
    ModelManager* model_m;
public:
    ObjectRenderer(TextureManager* textureManager, ModelManager* modelManager) : texture_m(textureManager), model_m(modelManager) {};

    virtual void render(Shader* shader) = 0;

    void useAtlas(size_t location) const;
};

#endif