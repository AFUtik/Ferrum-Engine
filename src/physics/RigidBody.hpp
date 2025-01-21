#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP

#include "glm/glm.hpp"
#include "glm/ext.hpp"

class RigidBody {
public:
    glm::mat4 model_mat;
    glm::mat2 rotation_mat;

    glm::vec3 pixel_position;
    glm::vec3 position;
    glm::vec2 velocity;
    glm::vec2 acceleration;
    glm::vec2 force;
    glm::vec2 dir;
    
    float mass;
    float max_speed;
    float time_elapsed;
    float friction_coefficient;
    bool constant_acceleration;

    float pixel_scale_factor = 0.03125f;
    bool pixel_perfect = false;

    RigidBody(glm::vec3 position, glm::vec2 acceleration, float max_speed);
    RigidBody(glm::vec3 position, float mass, float max_speed);

    void set_pixel_factor(int pixels_per_action, int texture_width);

    glm::vec3 pixel_perfect_clamp(glm::vec3 &pos);

    void apply_force(glm::vec2 force);

    void apply_direction(glm::vec2 dir);

    void update(float delta_time);
};

#endif