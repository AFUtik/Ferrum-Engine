#include "GameObject.hpp"

RigidBody& PhysicGameObject::getPhysicBody() {
    return rigidbody;
}

const glm::vec3& PhysicGameObject::getTransform() {
    return rigidbody.pixel_perfect ? rigidbody.pixel_position : rigidbody.position;
}