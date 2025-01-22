#ifndef HITBOX_HPP
#define HITBOX_HPP

#include "glm/glm.hpp"

class ColliderBox {
public:
    float time_elapsed;
    float friction;
    glm::vec2 min; 
    glm::vec2 max; 

    virtual ~ColliderBox() {}

    virtual bool checkCollision(const ColliderBox& other) const = 0;

    virtual glm::vec2 getPosition() const = 0;
};

//class AABB : public ColliderBox {
//public:
//    glm::vec2 min; 
//    glm::vec2 max; 
//
//    AABB(const glm::vec2& min, const glm::vec2& max)
//        : min(min), max(max) {}
//
//    bool checkCollision(const ColliderBox& other) const override {
//        const AABB* otherAABB = dynamic_cast<const AABB*>(&other);
//        if (otherAABB) {
//            return (max.x >= otherAABB->min.x && min.x <= otherAABB->max.x) &&
//                   (max.y >= otherAABB->min.y && min.y <= otherAABB->max.y);
//        }
//        return false;
//    }
//
//    glm::vec2 getPosition() const override {
//        return (min + max) / 2.0f; 
//    }
//};

#endif