#include "Tile.hpp"
#include "Chunks.hpp"
#include "Chunk.hpp"
#include "iostream"

#include <glm/glm.hpp>

using namespace glm;

#include <math.h>
#include <limits.h>

Chunks::Chunks() {

}

void Chunks::set(int w, int h) {
	volume = w * h;
	chunks = new Chunk * [volume];

	int index = 0;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++, index++) {
			chunks[index] = new Chunk(x, y);
		}
	}

	this->w = w; 
	this->h = h;
}

Chunks::~Chunks() {
	for (size_t i = 0; i < volume; i++) {
		delete chunks[i];
	}
	delete[] chunks;
}

//GridCollider* Chunks::getGridCollider(int x, int y) {
//	int cx = x / CHUNK_W;
//	int cy = x / CHUNK_H;
//	if (x < 0) cx--;
// 	if (y < 0) cy--;
//	if (cx < 0 || cy < 0 || cx >= w || cy >= h)
// 		return nullptr;
//	return chunks[cy*h + cx]->grid_collider;
//}
//
//block* Chunks::get(int x, int y, int z) {
//	int cx = x / CHUNK_W;
//	int cy = y / CHUNK_H;
//	int cz = z / CHUNK_D;
//	if (x < 0) cx--;
//	if (y < 0) cy--;
//	if (z < 0) cz--;
//	if (cx < 0 || cy < 0 || cz < 0 || cx >= w || cy >= h || cz >= d)
//		return nullptr;
//	Chunk* chunk = chunks[(cy * d + cz) * w + cx];
//	int lx = x - cx * CHUNK_W;
//	int ly = y - cy * CHUNK_H;
//	int lz = z - cz * CHUNK_D;
//	return &chunk->blocks[(ly * CHUNK_D + lz) * CHUNK_W + lx];
//}
//
//unsigned char Chunks::getLight(int x, int y, int z, int channel) {
//	int cx = x / CHUNK_W;
//	int cy = y / CHUNK_H;
//	int cz = z / CHUNK_D;
//	if (x < 0) cx--;
//	if (y < 0) cy--;
//	if (z < 0) cz--;
//	if (cx < 0 || cy < 0 || cz < 0 || cx >= w || cy >= h || cz >= d)
//		return 0;
//	Chunk* chunk = chunks[(cy * d + cz) * w + cx];
//	int lx = x - cx * CHUNK_W;
//	int ly = y - cy * CHUNK_H;
//	int lz = z - cz * CHUNK_D;
//	return chunk->lightmap->get(lx, ly, lz, channel);
//}
//
//Chunk* Chunks::getChunkByBlock(int x, int y, int z) {
//	int cx = x / CHUNK_W;
//	int cy = y / CHUNK_H;
//	int cz = z / CHUNK_D;
//	if (x < 0) cx--;
//	if (y < 0) cy--;
//	if (z < 0) cz--;
//	if (cx < 0 || cy < 0 || cz < 0 || cx >= w || cy >= h || cz >= d)
//		return nullptr;
//	return chunks[(cy * d + cz) * w + cx];
//}
//
//Chunk* Chunks::getChunk(int x, int y, int z) {
//	if (x < 0 || y < 0 || z < 0 || x >= w || y >= h || z >= d)
//		return nullptr;
//	return chunks[(y * d + z) * w + x];
//}
//
//void Chunks::set(int x, int y, int z, int id) {
//	int cx = x / CHUNK_W;
//	int cy = y / CHUNK_H;
//	int cz = z / CHUNK_D;
//	if (x < 0) cx--;
//	if (y < 0) cy--;
//	if (z < 0) cz--;
//	if (cx < 0 || cy < 0 || cz < 0 || cx >= w || cy >= h || cz >= d)
//		return;
//	Chunk* chunk = chunks[(cy * d + cz) * w + cx];
//	int lx = x - cx * CHUNK_W;
//	int ly = y - cy * CHUNK_H;
//	int lz = z - cz * CHUNK_D;
//	chunk->blocks[(ly * CHUNK_D + lz) * CHUNK_W + lx].id = id;
//	chunk->modified = true;
//
//	if (lx == 0 && (chunk = getChunk(cx - 1, cy, cz))) chunk->modified = true;
//	if (ly == 0 && (chunk = getChunk(cx, cy - 1, cz))) chunk->modified = true;
//	if (lz == 0 && (chunk = getChunk(cx, cy, cz - 1))) chunk->modified = true;
//
//	if (lx == CHUNK_W - 1 && (chunk = getChunk(cx + 1, cy, cz))) chunk->modified = true;
//	if (ly == CHUNK_H - 1 && (chunk = getChunk(cx, cy + 1, cz))) chunk->modified = true;
//	if (lz == CHUNK_D - 1 && (chunk = getChunk(cx, cy, cz + 1))) chunk->modified = true;
//}
//
//void Chunks::write(unsigned char* dest) {
//	size_t index = 0;
//	for (size_t i = 0; i < volume; i++) {
//		Chunk* chunk = chunks[i];
//		for (size_t j = 0; j < CHUNK_VOL; j++, index++) {
//			dest[index] = chunk->blocks[j].id;
//		}
//	}
//}
//
//void Chunks::read(unsigned char* source) {
//	size_t index = 0;
//	for (size_t i = 0; i < volume; i++) {
//		Chunk* chunk = chunks[i];
//		for (size_t j = 0; j < CHUNK_VOL; j++, index++) {
//			chunk->blocks[j].id = source[index];
//		}
//		chunk->modified = true;
//	}
//}