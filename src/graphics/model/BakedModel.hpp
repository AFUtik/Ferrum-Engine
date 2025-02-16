#ifndef BAKEDMODEL_HPP
#define BAKEDMODEL_HPP

#include "../texture/GLTexture.hpp"
#include "Mesh.hpp"

class Tilemap;
struct TextureRegion;

class GameObject;
struct Instance;

struct InstanceModelData {
    Instance *instance = nullptr;
    GameObject *object = nullptr;

    size_t instance_id;
};

class BakedModel {
protected:
    TextureRegion* texture_reg;
    Tilemap* tilemap;

    std::unique_ptr<Mesh> mesh;
    std::vector<InstanceModelData> model_instances;

    GLTexture* texture;

    unsigned int render_mode = 4; // GL_TRIANGLES //

    friend class ModelManager;
public:
    BakedModel(Mesh* mesh) : mesh(mesh) {
        model_instances.resize(1);
    };

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