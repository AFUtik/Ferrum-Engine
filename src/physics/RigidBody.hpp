#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP

#include "glm/glm.hpp"
#include "glm/ext.hpp"

class RigidBody {
public:
    glm::mat4 model_mat;
    glm::mat2 rotation_mat;
    
    glm::vec3 pixelated_position;
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

    RigidBody(glm::vec3 pos, glm::vec2 vel, float m) : position(pos), pixelated_position(pos), velocity(vel), mass(m), model_mat(1.0f), force(0.0f), acceleration(0.0f) {};

    void apply_force(glm::vec2 applied_force);

    glm::vec2 getAcceleration();

    void update(float delta_time);
};

#endif