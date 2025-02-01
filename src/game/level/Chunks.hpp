#ifndef CHUNKS_HPP
#define CHUNKS_HPP

#include <cstdint>
#include <queue>

class Chunk;
class GridCollider;
struct Tile;

class Chunks {
public:
	unsigned int w, h;
	Chunk** chunks;
	size_t volume;
	
	std::queue<Chunk*> chunks_to_load, chunks_to_unload;

	Chunks();
	~Chunks();

	void load(int x, int y);
	void unload(int x, int y);

	void set(int w, int h);

	Chunk* getChunk(int x, int y);
	Chunk* getChunkByBlock(int x, int y);

	//GridCollider* getGridCollider(int x, int y);
	
	//block* get(int x, int y, int z);
	//unsigned char getLight(int x, int y, int z, int channel);
	//void set(int x, int y, int z, int id);

	//void write(unsigned char* dest);
	//void read(unsigned char* source);
};

#endif // !CHUNKS_HPP
