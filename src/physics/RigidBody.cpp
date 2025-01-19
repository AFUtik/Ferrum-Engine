#include "RigidBody.hpp"

void RigidBody::apply_force(glm::vec2 applied_force) {
    force += applied_force;
}

void RigidBody::update(float delta_time) {
    glm::vec2 acceleration = force / mass;

    velocity += acceleration * delta_time;
    if (glm::length(velocity) > max_speed) {
        velocity = glm::normalize(velocity) * max_speed;  
    }

    position += glm::vec3(velocity, 0.0f) * delta_time;

    model_mat = pixel_perfect ? glm::translate(glm::mat4(1.0f), glm::floor(position/pixel_scale_factor)*pixel_scale_factor) : glm::translate(glm::mat4(1.0f), position);

    force = glm::vec2(0.0f, 0.0f);
    time_elapsed += delta_time;
}