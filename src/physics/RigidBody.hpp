#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP

#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <functional>

class GridCollider;

class RigidBody {
public:
    glm::mat4 model_mat; // Determines how object is placed in the space. This matrix passes into vertex shader //
    glm::mat2 rotation_mat;

    glm::vec3 pixel_position;
    glm::vec3 position;
    glm::vec2 velocity;
    glm::vec2 acceleration;
    glm::vec2 force;
    glm::vec2 dir;
    
    // Is used for anti-cobblestone. //
    //glm::vec2 last_dir; 
    //glm::vec2 last_pos;
    
    float mass;
    float max_speed;
    float time_elapsed;
    float friction;
    bool constant_acceleration;
    bool on_ground;

    // Determines one pixel's distance in the game space. Can be changed //
    float pixel_scale_factor = 0.03125f; 
    bool pixel_perfect = false;

    std::function<GridCollider*(int, int)> collider_getter;
    //std::function<GridCollider*(int, int)> hitbox_getter;

    // Anti-Cobblestone variable //
    // This variable fixes jitter diagonal motion when pixel perfect is enabled. //
    // Can modify non-pixel position during the diagonal motion. Use only for pixel perfect motion. //
    //bool anti_cb; 
    //glm::vec2 anti_cb_dir; // Values from 0.0 to 1.0 //

    RigidBody(glm::vec3 position, glm::vec2 acceleration, float max_speed); // Uses directions for motion with constant acceleration //
    RigidBody(glm::vec3 position, float mass, float max_speed); // Uses force for motion //
    
    glm::vec3 pixel_perfect_clamp(glm::vec3 &pos); // Method converts non-pixel coordinates to pixel perfect coordinates. //

    void set_grid_collider_getter(std::function<GridCollider*(int, int)>);

    //void set_hitbox_getter(std::function<GridCollider*(int, int)>);

    void set_pixel_factor(int pixels_per_action, int texture_width);

    void apply_force(glm::vec2 force);

    void apply_direction(glm::vec2 dir);

    void update(float delta_time);
};

#endif