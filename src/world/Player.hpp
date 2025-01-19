#ifndef PLAYER_HPP
#define PLAYER_HPP

class RigidBody;
class Mesh;

class Player {
public:
    RigidBody* rigid_body;
    Mesh* mesh;
    float buffer[5*6];
    
    Player() : rigid_body(nullptr), mesh(nullptr) {};
    ~Player();

    void render();
};

#endif