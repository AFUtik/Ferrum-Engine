#ifndef GAMEOBJECT
#define GAMEOBJECT

#include "../physics/RigidBody.hpp"
#include "GameProperties.hpp"

class StaticGameObject {
protected:
    GameProperties properties;

    std::string object_id;
public:
    StaticGameObject(std::string id) : object_id(id) {};

    inline const std::string& getObjectId() {return object_id;}
};

class PhysicGameObject : public StaticGameObject {
private:
    RigidBody rigidbody;
public:
    const glm::vec3& getTransform();
    RigidBody& getPhysicBody();
};

#endif