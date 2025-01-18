#ifndef PLAYER_HPP
#define PLAYER_HPP

class Mesh;
class RigidBody;

class Player {
public:
    RigidBody* rigid_body;
    Mesh* mesh;

    void render();

    Player();
    ~Player();
};

#endif