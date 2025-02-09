#ifndef ENTITYRENDERER_HPP
#define ENTITYRENDERER_HPP

#include "ObjectRenderer.hpp"
#include "../../utils/math/MatrixUtils.hpp"

#define TEST_ANIMATION 0

class EntitySystem;

class EntityRenderer : public ObjectRenderer {
protected:
    EntitySystem* entity_s;
public:
    EntityRenderer(EntitySystem* entity_s) : entity_s(entity_s) {};

    void render() override;
};

#endif