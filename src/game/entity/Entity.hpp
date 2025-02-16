#ifndef ENTITY_HPP
#define ENTITY_HPP

class EntitySystem;

#include "../GameObject.hpp"

class Entity : public PhysicGameObject {
protected:
    EntitySystem* system;

    friend class EntitySystem;
public:
    float anim_time = 0.0f;
    Entity(std::string object_id) : PhysicGameObject(object_id) {};

    void onUpdate(float delta);
    void onCreate();
};

#endif