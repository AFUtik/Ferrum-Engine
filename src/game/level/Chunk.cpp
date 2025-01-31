#include "Chunk.hpp"

#include "Tile.hpp"
#include "Chunk.hpp"

#include <iostream>

#include <cmath>

Chunk::Chunk(int x, int y) : x(x), y(y) {
	tiles = new Tile[CHUNK_VOL];
	for (int y = 0; y < CHUNK_H; y++) {
		for (int x = 0; x < CHUNK_W; x++) {
			tiles[y * CHUNK_H + x].id = 1;
		}
	}
}

Chunk::~Chunk() {
	delete[] tiles;
}