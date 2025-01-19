#include "../physics/RigidBody.hpp"
#include "../graphics/Mesh.hpp"
#include "Player.hpp"

#define VERTEX_SIZE (3+2)
#define VERTEX(INDEX, X,Y,Z, U,V) buffer[INDEX+0] = (X);\
								  buffer[INDEX+1] = (Y);\
								  buffer[INDEX+2] = (Z);\
								  buffer[INDEX+3] = (U);\
								  buffer[INDEX+4] = (V);\
								  INDEX += VERTEX_SIZE;

int attrs[] = { 3,2,0, 0 };

void Player::render() {
    int index = 0;
    int id = 1;

    float uvsize = 1.0f / 16.0f;
	float u = (id % 16) * uvsize;
	float v = 1 - ((1 + id / 16) * uvsize);

    VERTEX(index, 0 - 0.5f, 0 - 0.5f, 0, u, v);
	VERTEX(index, 0 + 0.5f, 0 + 0.5f, 0, u + uvsize, v + uvsize);
	VERTEX(index, 0 - 0.5f, 0 + 0.5f, 0, u, v + uvsize);
	VERTEX(index, 0 - 0.5f, 0 - 0.5f, 0, u, v);
	VERTEX(index, 0 + 0.5f, 0 - 0.5f, 0, u + uvsize, v);
	VERTEX(index, 0 + 0.5f, 0 + 0.5f, 0, u + uvsize, v + uvsize);
	
	//VERTEX(index, x - 0.5f, y - 0.5f, 0, u, v);
	//VERTEX(index, x + 0.5f, y + 0.5f, 0, u + uvsize, v + uvsize);
	//VERTEX(index, x - 0.5f, y + 0.5f, 0, u, v + uvsize);
	//VERTEX(index, x - 0.5f, y - 0.5f, 0, u, v);
	//VERTEX(index, x + 0.5f, y - 0.5f, 0, u + uvsize, v);
	//VERTEX(index, x + 0.5f, y + 0.5f, 0, u + uvsize, v + uvsize);

    mesh = new Mesh(buffer, index / VERTEX_SIZE, attrs);
}

Player::~Player() {
    delete rigid_body;
    delete mesh;
}