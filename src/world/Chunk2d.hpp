#ifndef CHUNK2D_HPP
#define CHUNK2D_HPP

#include <vector>

#define CHUNK_W 32
#define CHUNK_H 32
#define CHUNK_VOL (CHUNK_W * CHUNK_H)

struct Tile;
struct Entity;
class Lightmap;
class Mesh;

class Chunk2d {
public:
	int x, y;
	Tile* tiles;
    std::vector<Entity*> entities;
	Lightmap* lightmap;
	Mesh* mesh;

	unsigned char biome;
	bool isDirty = true;
	
	Chunk2d(int x, int y);
	~Chunk2d();
};

#endif // !CHUNK_HPP
