#include "../physics/RigidBody.hpp"
#include "Entity.hpp"

//Entity::Entity(size_t id) : id(id) {
//
//}

Entity::Entity(size_t id) : system(nullptr), id(id) {

}

size_t Entity::getId() {
    return id;
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