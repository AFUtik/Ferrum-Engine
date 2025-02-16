#include "Entity.hpp"

void Entity::onUpdate(float delta) {
    anim_time += delta;
    if(anim_time > 6.0f) anim_time = 0.0f;

    rigidbody.update(delta);
}

void Entity::onCreate() {
 
}