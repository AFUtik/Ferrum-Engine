#ifndef BAKEDMODEL_HPP
#define BAKEDMODEL_HPP

class Mesh;
class GLTexture;
class TextureAtlasPos;

class BakedModel {
protected:
    //GLTexture* gl_texture;
    Mesh* mesh;

    friend class ModelManager;
public:
    BakedModel(Mesh* mesh) : mesh(mesh) {};
    ~BakedModel();

    //TextureAtlasPos* getAtlasPos();
    //GLTexture* getGLTexture();

    void render();
};

#endif