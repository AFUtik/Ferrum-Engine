#include "Entity.hpp"

Entity::Entity(size_t id) : system(nullptr), id(id) {

}

size_t Entity::getId() {
    return id;
}

RigidBody* Entity::getPhysicBody() {
    return rigid_body.get();
}

const glm::vec3& Entity::getTransform() {
    return rigid_body->pixel_perfect ? rigid_body->pixel_position : rigid_body->position;
}

void Entity::onUpdate(float delta) {
    anim_time += delta;
    if(anim_time > 6.0f) anim_time = 0.0f;

    rigid_body->update(delta);
}

void Entity::onCreate() {
 
}