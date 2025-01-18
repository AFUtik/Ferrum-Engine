#include <iostream>

#include "../world/Tile.hpp"
#include "../world/Chunk2d.hpp"
#include "Mesh.hpp"
#include "Renderer.hpp"

#define VERTEX_SIZE (3 + 2 + 0)
//
//#define CDIV(X,A) (((X) < 0) ? ((X) / (A) - 1) : ((X) / (A)))
//#define LOCAL_NEG(X, SIZE) (((X) < 0) ? ((SIZE)+(X)) : (X))
//#define LOCAL(X, SIZE) ((X) >= (SIZE) ? ((X) - (SIZE)) : LOCAL_NEG(X, SIZE))
//#define IS_CHUNK(X,Y,Z) (GET_CHUNK(X,Y,Z) != nullptr)
//#define GET_CHUNK(X,Y,Z) (chunks[((CDIV(Y, CHUNK_H)+1) * 3 + CDIV(Z, CHUNK_D) + 1) * 3 + CDIV(X, CHUNK_W) + 1])
//
//#define VOXEL(X,Y,Z) (GET_CHUNK(X,Y,Z)->blocks[(LOCAL(Y, CHUNK_H) * CHUNK_D + LOCAL(Z, CHUNK_D)) * CHUNK_W + LOCAL(X, CHUNK_W)])
//#define IS_BLOCKED(X,Y,Z) (IS_CHUNK(X, Y, Z) && VOXEL(X, Y, Z).id)

#define VERTEX(INDEX, X,Y,Z, U,V) buffer[INDEX+0] = (X);\
								  buffer[INDEX+1] = (Y);\
								  buffer[INDEX+2] = (Z);\
								  buffer[INDEX+3] = (U);\
								  buffer[INDEX+4] = (V);\
								  INDEX += VERTEX_SIZE;

int chunk_attrs[] = { 3,2,0, 0 };

Renderer::Renderer(size_t capacity) : capacity(capacity) {
	buffer = new float[capacity * VERTEX_SIZE * 5];
}

Renderer::~Renderer() {
	delete[] buffer;
}

void Renderer::render_chunk2d(Chunk2d* chunk, const Chunk2d** chunks) {
	size_t index = 0;
	for (int y = 0; y < 32; y++) {
		for (int x = 0; x < 32; x++) {
			Tile& tile = chunk->tiles[y * CHUNK_H + x];
			unsigned int id = tile.id;

			if (!id) {
				continue;
			}

			//if (id == 1) {
			//	std::cout << GET_CHUNK(x, y, z) << std::endl;
			//}
			float l;
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
	}
	chunk->mesh = new Mesh(buffer, index / VERTEX_SIZE, chunk_attrs);
}