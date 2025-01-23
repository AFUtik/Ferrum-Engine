#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>

class DrawContext;
class RigidBody;
class Mesh;

class Entity {
public:
    RigidBody* rigid_body;
    unsigned int unique_id;
    unsigned int texture_id;
    bool rendered;

    virtual Entity* instance() = 0;

    Entity();
    ~Entity();

    std::string tag;
    
};

#endif