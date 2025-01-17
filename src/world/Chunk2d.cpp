#include "Chunk2d.hpp"

#include "Tile.hpp"
#include "Chunk2d.hpp"

#include <iostream>

#include <cmath>

Chunk2d::Chunk2d(int x, int y) : x(x), y(y) {
	const float scale = 0.015f;
	tiles = new Tile[CHUNK_VOL];
	for (int y = 0; y < CHUNK_H; y++) {
		for (int x = 0; x < CHUNK_W; x++) {
			int real_x = x + this->x * CHUNK_W;
			int real_y = y + this->y * CHUNK_H;
			tiles[y * CHUNK_H + x].id = 1;
		}
	}
}

Chunk2d::~Chunk2d() {
	delete[] tiles;
}