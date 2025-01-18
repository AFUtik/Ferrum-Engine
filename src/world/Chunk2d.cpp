#include "Chunk2d.hpp"

#include "Tile.hpp"
#include "Chunk2d.hpp"

#include <iostream>

#include <cmath>

Chunk2d::Chunk2d(int x, int y) : x(x), y(y) {
	tiles = new Tile[CHUNK_VOL];
	for (int y = 0; y < CHUNK_H; y++) {
		for (int x = 0; x < CHUNK_W; x++) {
			tiles[y * CHUNK_H + x].id = 2;
		}
	}
}

Chunk2d::~Chunk2d() {
	delete[] tiles;
}