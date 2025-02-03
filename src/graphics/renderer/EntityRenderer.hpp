#ifndef ENTITYRENDERER_HPP
#define ENTITYRENDERER_HPP

#include "ObjectRenderer.hpp"
#include "../../math/MatrixUtils.hpp"

class EntitySystem;

class EntityRenderer {
protected:
    ObjectRenderer* object_renderer;
    TextureManager* texture_m;
    ModelManager* model_m;
    EntitySystem* entity_s;

    float instance_data[18];
public:
    EntityRenderer(ObjectRenderer* object_renderer, TextureManager* tex_m, ModelManager* model_m, EntitySystem* entity_s) : 
    texture_m(tex_m), model_m(model_m), entity_s(entity_s), object_renderer(object_renderer) {
        Matrix4x4ArrayUtils::fill(instance_data, 1.0f);
    };

    void render();
};

#endif