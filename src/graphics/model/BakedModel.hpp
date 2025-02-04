#ifndef BAKEDMODEL_HPP
#define BAKEDMODEL_HPP

#include <unordered_map>

#include "../animation/SpriteAnimation.hpp"
#include "../texture/GLTexture.hpp"
#include "Mesh.hpp"

class TextureAtlas;
class TextureAtlasPos;

class BakedModel {
protected:
    TextureAtlasPos* atlas_pos;
    TextureAtlas* atlas;
    std::unordered_map<size_t, std::unique_ptr<SpriteAnimation>> animations;

    std::unique_ptr<GLTexture> mesh_texture;
    std::unique_ptr<Mesh> mesh;
    unsigned int render_mode = 4; // GL_TRIANGLES //

    friend class ModelManager;
public:
    BakedModel(Mesh* mesh) : mesh(mesh) {};

    inline void setRenderMode(unsigned int value) {render_mode = value;};

    SpriteAnimation* getSpriteAnimation(size_t location);

    Mesh* getMesh();

    void bindTexture();
    void render();
};

#endif