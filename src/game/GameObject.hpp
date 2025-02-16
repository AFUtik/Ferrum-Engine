#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "GameProperties.hpp"

#include "../physics/RigidBody.hpp"

#include "animation/SpriteAnimator.hpp"

class StaticGameObject {
protected:
    SpriteAnimator* animator;
    AnimationInfo anim_info;

    GameProperties properties;

    std::string object_id;
public:
    StaticGameObject(std::string id) : object_id(id) {};

    inline const std::string& getObjectId() {return object_id;}
};

class PhysicGameObject : public StaticGameObject {
protected:
    RigidBody rigidbody;
public:
    PhysicGameObject(std::string id) : StaticGameObject(id), rigidbody(glm::vec3(0.0f), 0.0f, 0.0f) {};

    const glm::vec3& getTransform();
    RigidBody& getPhysicBody();
};

#endif