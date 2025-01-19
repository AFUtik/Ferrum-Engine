#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "glm/glm.hpp"

class Collider {
public:
    virtual ~Collider() {}

    virtual bool checkCollision(const Collider& other) const = 0;

    virtual glm::vec2 getPosition() const = 0;
};

class AABB : public Collider {
public:
    glm::vec2 min; 
    glm::vec2 max; 

    AABB(const glm::vec2& min, const glm::vec2& max)
        : min(min), max(max) {}

    bool checkCollision(const Collider& other) const override {
        const AABB* otherAABB = dynamic_cast<const AABB*>(&other);
        if (otherAABB) {
            return (max.x >= otherAABB->min.x && min.x <= otherAABB->max.x) &&
                   (max.y >= otherAABB->min.y && min.y <= otherAABB->max.y);
        }
        return false;
    }

    glm::vec2 getPosition() const override {
        return (min + max) / 2.0f; 
    }
};

#endif