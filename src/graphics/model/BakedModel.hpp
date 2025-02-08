#ifndef BAKEDMODEL_HPP
#define BAKEDMODEL_HPP

#include "../animation/SpriteAnimator.hpp"
#include "../texture/GLTexture.hpp"
#include "Mesh.hpp"
#include "Instance.hpp"

class TextureAtlas;
class TextureAtlasPos;

struct InstanceModelData : public Instance {
    size_t object_id;
    bool active = false;
    float animation_time = 0.0f;
    unsigned int current_state = 0;

    inline void clearAnimation() {
        animation_time = 0.0f;
        current_state = 0;
    }
};

class BakedModel {
protected:
    TextureAtlasPos* atlas_pos;
    TextureAtlas* atlas;

    std::unique_ptr<SpriteAnimator> animator;

    std::vector<InstanceModelData> instances;
    std::unique_ptr<Mesh> mesh;

    GLTexture* mesh_texture;

    unsigned int render_mode = 4; // GL_TRIANGLES //

    friend class ModelManager;
public:
    BakedModel(Mesh* mesh) : mesh(mesh) {
        instances.resize(1);
    };

    inline SpriteAnimator* getSpriteAnimator() {return animator.get();}

    inline bool isCustomAtlas() {return true;}
    inline void setRenderMode(unsigned int value) {render_mode = value;};

    const unsigned int& getInstancesAmount();
    InstanceModelData& getInstanceModelData(const size_t &index);
    Mesh* getMesh();

    void updateInstance(const size_t &index);
    void updateInstances(const size_t &size);

    void bindTexture();
    void render();
};

#endif