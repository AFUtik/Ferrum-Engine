#ifndef BAKEDMODEL_HPP
#define BAKEDMODEL_HPP

#include "../texture/GLTexture.hpp"
#include "Mesh.hpp"

class Tilemap;
struct TextureRegion;

class GameObject;
struct Instance;

class BakedModel {
protected:
    TextureRegion* texture_reg;
    Tilemap* tilemap;

    std::unique_ptr<Mesh> mesh;
    GLTexture* texture;

    unsigned int render_mode = 4; // GL_TRIANGLES //

    friend class ModelManager;
public:
    BakedModel(Mesh* mesh) : mesh(mesh) {};

    inline void setRenderMode(unsigned int value) {render_mode = value;};
    Mesh* getMesh();

    void updateInstance(const size_t &index);
    void updateInstances(const size_t &size);

    void bindTexture();
    void render();
};

#endif