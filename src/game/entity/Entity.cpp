#include "Entity.hpp"

Entity::Entity(std::string tag) : system(nullptr), tag(tag) {

}

const std::string& Entity::getTag() {
    return tag;
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