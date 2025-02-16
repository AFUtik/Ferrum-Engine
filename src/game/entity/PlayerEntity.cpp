#include "PlayerEntity.hpp"

PlayerEntity::PlayerEntity() : Entity("player") {
    rigidbody = RigidBody(glm::vec3(0.0f), glm::vec2(2.0f, 2.0f), 1.5f);
}