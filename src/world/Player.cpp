#include "Player.hpp"
#include "../physics/RigidBody.hpp"

void Player::render() {
    float uvsize = 1.0f / 16.0f;
	float u = (id % 16) * uvsize;
	float v = 1 - ((1 + id / 16) * uvsize);
	
	VERTEX(index, x - 0.5f, y - 0.5f, 0, u, v);
	VERTEX(index, x + 0.5f, y + 0.5f, 0, u + uvsize, v + uvsize);
	VERTEX(index, x - 0.5f, y + 0.5f, 0, u, v + uvsize);
	VERTEX(index, x - 0.5f, y - 0.5f, 0, u, v);
	VERTEX(index, x + 0.5f, y - 0.5f, 0, u + uvsize, v);
	VERTEX(index, x + 0.5f, y + 0.5f, 0, u + uvsize, v + uvsize);
}

Player::~Player() {
    delete rigid_body;
}