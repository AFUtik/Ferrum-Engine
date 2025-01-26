#ifndef BAKEDMODEL_HPP
#define BAKEDMODEL_HPP

class Mesh;
class Texture;

class BakedModel {
protected:
    Mesh* mesh;
    Texture* texture;

    friend class ModelManager;
public:
    BakedModel(Mesh* mesh, Texture* texture) : mesh(mesh), texture(texture) {};
    ~BakedModel();

    Texture* getTexture();

    void render();
};

#endif