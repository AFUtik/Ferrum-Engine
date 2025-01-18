#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP

#include "glm/glm.hpp"
#include "glm/ext.hpp"

class RigidBody {
public:
    glm::mat4 model_mat;
    glm::mat2 rotation_mat;
    
    glm::vec3 position;
    glm::vec2 velocity;
    glm::vec2 acceleration;
    glm::vec2 force;
    float mass;
    float max_speed;
    float max_horizontal_acceleration;
    float max_vertical_acceleration;
    float acceleration_time;
    float time_elapsed;

    RigidBody(glm::vec3 pos, glm::vec2 vel, float m) : position(pos), velocity(vel), mass(m) {};

    void apply_force(glm::vec2 applied_force) {
        force += applied_force;
    }

    glm::vec2 getAcceleration() {
        float x_t = time_elapsed / max_horizontal_acceleration;
        float x_accelerationFactor = 1.0f - (x_t * x_t);
        float x_acc = max_horizontal_acceleration * x_accelerationFactor;
        
        float y_t = time_elapsed / max_vertical_acceleration;
        float y_accelerationFactor = 1.0f - (y_t * y_t);
        float y_acc = max_horizontal_acceleration * y_accelerationFactor;
        
        return glm::vec2(x_acc, y_acc);
    }

    void update(float delta_time) {
        glm::vec2 acceleration = force / mass;
        velocity += acceleration * delta_time;
        position += glm::vec3(velocity, 0.0f) * delta_time;
        model_mat = glm::translate(glm::mat4(1.0f), position);

        force = glm::vec2(0.0f, 0.0f);
        time_elapsed += delta_time;
    }
};

#endif