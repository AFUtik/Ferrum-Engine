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
    float acceleration_time;
    float time_elapsed;

    float pixel_scale_factor = 0.03125f;
    bool pixel_perfect = false;

    RigidBody(glm::vec3 pos, glm::vec2 vel, float m, float max_speed) : position(pos), velocity(vel), mass(m), model_mat(1.0f), force(0.0f), acceleration(0.0f)
, max_speed(max_speed), acceleration_time(20.0f) {};

    inline void set_pixel_factor(float pixels_motion, float texture_width) {
        pixel_scale_factor = pixels_motion/(texture_width*2);
    }

    void apply_force(glm::vec2 applied_force);

    void update(float delta_time);
};

#endif