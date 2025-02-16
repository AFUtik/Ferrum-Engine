#include "Chunk.hpp"

#include "Tile.hpp"
#include "Chunk.hpp"

#include <iostream>

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp> 

Chunk::Chunk(int x, int y) : x(x), y(y) {
	tiles = new Tile[CHUNK_VOL];
	for (int y = 0; y < CHUNK_H; y++) {
		for (int x = 0; x < CHUNK_W; x++) {
			int real_x = x + this->x * CHUNK_W;
			int real_y = y + this->y * CHUNK_H;

			float n = glm::perlin(glm::vec2(real_x, real_y) * 0.5f);
			if(n > 0.15f) {
				tiles[y * CHUNK_H + x].id = "asd";
			} else {
				tiles[y * CHUNK_H + x].id = "asd";
			}

			
		}
	}
}

Chunk::~Chunk() {
	delete[] tiles;
}