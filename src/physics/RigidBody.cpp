#include "RigidBody.hpp"
#include <iostream>

RigidBody::RigidBody(glm::vec3 pos, glm::vec2 acceleration, float max_speed) : 
position(pos), velocity(0.0f), acceleration(acceleration), mass(0.0f), 
max_speed(max_speed), friction(0.0f), dir(0.0f) {
    constant_acceleration = true;
}

RigidBody::RigidBody(glm::vec3 pos, float mass, float max_speed) : 
position(pos), velocity(0.0f), acceleration(0.0f), mass(mass), 
max_speed(max_speed), friction(0.0f), dir(0.0f) {
    constant_acceleration = false;
}

void RigidBody::apply_direction(glm::vec2 dir) {
    this->dir += dir;
}

void RigidBody::apply_force(glm::vec2 force) {
    this->force += force;
}

void RigidBody::set_pixel_factor(int pixels_per_action, int texture_width) {
    pixel_scale_factor = (float)pixels_per_action/(float)(texture_width*2);
}

glm::vec3 RigidBody::pixel_perfect_clamp(glm::vec3 &pos) {
    return glm::floor(pos/pixel_scale_factor)*pixel_scale_factor;
}

void RigidBody::update(float delta_time) {
    glm::vec2 new_acceleration = constant_acceleration ? acceleration * dir : force / mass;

    velocity += new_acceleration * delta_time;
    velocity += -velocity * friction * delta_time;
    glm::vec2 normalized_vel = glm::normalize(velocity);
    if (glm::length(velocity) > max_speed) { // Restricts the movement to certain max speed //
        velocity = normalized_vel * max_speed;  
    }
    
    position += glm::vec3(velocity * delta_time, 0.0f);

    if(pixel_perfect) pixel_position = pixel_perfect_clamp(position); 

    //position = glm::vec3(pixel_pos.x, pixel_pos.y, position.z);
    //last_dir = dir;
    //last_pos = pixel_position;
    dir = glm::vec2(0.0f, 0.0f);
    force = glm::vec2(0.0f, 0.0f);
    //time_elapsed += delta_time;
}