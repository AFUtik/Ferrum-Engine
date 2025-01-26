#include "PlayerEntity.hpp"
#include "../physics/RigidBody.hpp"

PlayerEntity::PlayerEntity() {
    rigid_body = std::make_unique<RigidBody>(glm::vec3(0.0f), glm::vec2(2.0f, 2.0f), 1.5f);
}