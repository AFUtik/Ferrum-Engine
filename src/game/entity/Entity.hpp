#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <memory>
#include <string>
#include "glm/glm.hpp"

class EntitySystem;

#include "../../physics/RigidBody.hpp"

class Entity {
protected:
    EntitySystem* system;
    std::unique_ptr<RigidBody> rigid_body;
    size_t id;
    bool show;

    friend class EntitySystem;
public:
    Entity(size_t id);
    // virtual ~Entity();

    size_t getId();
    const glm::vec3& getTransform();
    RigidBody* getPhysicBody();

    void onUpdate(float delta);
    void onCreate();
};

#endif