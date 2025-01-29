#ifndef BAKEDMODEL_HPP
#define BAKEDMODEL_HPP

class Mesh;
class GLTexture;
class TextureAtlasPos;

class BakedModel {
protected:
    Mesh* mesh;
    GLTexture* texture;

    friend class ModelManager;
public:
    BakedModel(Mesh* mesh, GLTexture* texture) : mesh(mesh), texture(texture) {};
    ~BakedModel();

    GLTexture* getTexture();

    void render();
};

#endif