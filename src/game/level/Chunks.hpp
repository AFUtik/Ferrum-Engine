#ifndef CHUNKS_HPP
#define CHUNKS_HPP

#include <cstdint>

class Chunk;
class GridCollider;
struct Tile;

class Chunks {
public:
	unsigned int w, h;
	Chunk** chunks;
	size_t volume;
	Chunks();
	~Chunks();

	void load();
	void set(int w, int h);
	GridCollider* getGridCollider(int x, int y);
	
	//block* get(int x, int y, int z);
	//Chunk* getChunk(int x, int y, int z);
	//Chunk* getChunkByBlock(int x, int y, int z);
	//unsigned char getLight(int x, int y, int z, int channel);
	//void set(int x, int y, int z, int id);

	//void write(unsigned char* dest);
	//void read(unsigned char* source);
};

#endif // !CHUNKS_HPP
