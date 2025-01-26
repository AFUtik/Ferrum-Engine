#ifndef ENTITYRENDERER_HPP
#define ENTITYRENDERER_HPP

//#include "Renderer.hpp"
//#include <vector>

class Shader;
class EntitySystem;
class ModelManager;

class EntityRenderer {
private:
    ModelManager* model_m;
    EntitySystem* entity_s;
public:
    EntityRenderer(ModelManager* model_m, EntitySystem* entity_s);
    //virtual ~EntityRenderer();

    void render(Shader* shader);
};

#endif