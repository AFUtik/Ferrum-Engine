#ifndef CHUNKRENDERER_HPP
#define CHUNKRENDERER_HPP

#include "ObjectRenderer.hpp"
//#include <vector>

class EntitySystem;

class EntityRenderer : public ObjectRenderer {
private:
    EntitySystem* entity_s;
public:
    EntityRenderer(TextureManager* tex_m, ModelManager* model_m, EntitySystem* entity_s) : 
    ObjectRenderer(tex_m, model_m), entity_s(entity_s) {};

    void render(Shader* shader) override;
};

#endif