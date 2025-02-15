#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <memory>
#include <string>
#include "glm/glm.hpp"

class EntitySystem;

#include "../../physics/RigidBody.hpp"
#include "../GameObject.hpp"
class Entity : public GameObject {
protected:
    EntitySystem* system;
    std::unique_ptr<RigidBody> rigid_body;

    friend class EntitySystem;
public:
    float anim_time = 0.0f;
    using GameObject::GameObject;


    void onUpdate(float delta);
    void onCreate();
};

#endif