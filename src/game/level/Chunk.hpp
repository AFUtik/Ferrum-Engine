#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <vector>

#define CHUNK_W 32
#define CHUNK_H 32
#define CHUNK_VOL (CHUNK_W * CHUNK_H)

struct Tile;
struct Entity;
class GridCollider;
class Lightmap;
class Mesh;

class Chunk {
public:
	int x, y;
	Tile* tiles;
    std::vector<Entity*> entities;
	GridCollider* grid_collider;
	Lightmap* lightmap;

	unsigned char biome;
	bool isDirty = false;
	
	Chunk(int x, int y);
	~Chunk();
};

#endif // !CHUNK_HPP
