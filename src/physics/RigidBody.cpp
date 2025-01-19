#include "RigidBody.hpp"

glm::vec2 RigidBody::getAcceleration() {
    float x_t = time_elapsed / max_horizontal_acceleration;
    float x_accelerationFactor = 1.0f - (x_t * x_t);
    float x_acc = max_horizontal_acceleration * x_accelerationFactor;
    
    float y_t = time_elapsed / max_vertical_acceleration;
    float y_accelerationFactor = 1.0f - (y_t * y_t);
    float y_acc = max_horizontal_acceleration * y_accelerationFactor;
    
    return glm::vec2(x_acc, y_acc);
}

void RigidBody::apply_force(glm::vec2 applied_force) {
    force += applied_force;
}

void RigidBody::update(float delta_time) {
    float pixel8 = 0.5f;
    float pixel4 = 0.125f;
    float pixel2 = 0.0625f;
    float pixel1 = 0.03125f;
    float pixel05 = 0.015625f;

    glm::vec2 acceleration = force / mass;
    velocity += acceleration * delta_time;
    position += glm::vec3(velocity, 0.0f) * delta_time;
    pixelated_position = floor(position/pixel1)*pixel1;
    model_mat = glm::translate(glm::mat4(1.0f), pixelated_position);

    force = glm::vec2(0.0f, 0.0f);
    time_elapsed += delta_time;
}