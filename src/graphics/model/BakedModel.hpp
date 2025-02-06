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

    SpriteAnimator animator;

    std::unique_ptr<GLTexture> mesh_texture;
    
    std::vector<InstanceModelData> instances;
    std::unique_ptr<Mesh> mesh;

    unsigned int render_mode = 4; // GL_TRIANGLES //

    friend class ModelManager;
public:
    BakedModel(Mesh* mesh) : mesh(mesh) {};

    SpriteAnimator* getSpriteAnimator();

    inline bool isCustomAtlas() {return true;}
    inline void setRenderMode(unsigned int value) {render_mode = value;};

    InstanceModelData& getInstanceModelData();
    Mesh* getMesh();

    inline unsigned int& getInstancesAmount() {return mesh->instance_count;}
    void updateInstance(const size_t &index);
    void updateInstances(const size_t &size);

    void bindTexture();
    void render();
};

#endif