#ifndef BAKEDMODEL_HPP
#define BAKEDMODEL_HPP

class Mesh;
class GLTexture;
class TextureAtlasPos;

#include "glm/glm.hpp"

class BakedModel {
protected:
    //GLTexture* gl_texture;
    Mesh* mesh;

    friend class ModelManager;
public:
    BakedModel(Mesh* mesh) : mesh(mesh) {};
    ~BakedModel();
    
    void clearInstances();
    void updateInstances(int size);
    void updateInstance(int index, glm::mat4 &transform);
    void render();
};

#endif