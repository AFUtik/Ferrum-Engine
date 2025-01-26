#include "../physics/RigidBody.hpp"
#include "Entity.hpp"

//Entity::Entity(size_t id) : id(id) {
//
//}

Entity::Entity() : system(nullptr) {

}

RigidBody* Entity::getPhysicBody() {
    return rigid_body.get();
}

glm::vec3 Entity::getTransform() {
    return rigid_body->position;
}

void Entity::onUpdate(float delta) {
    rigid_body->update(delta);
}

void Entity::onCreate() {
 
}