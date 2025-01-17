#ifndef CHUNKS_HPP
#define CHUNKS_HPP

#include <cstdint>

class Chunk2d;
struct block;

class Chunks {
public:
	unsigned int w, h, d;
	Chunk2d** chunks;
	size_t volume;
	Chunks(int w, int h);
	~Chunks();
	
	//block* get(int x, int y, int z);
	//Chunk* getChunk(int x, int y, int z);
	//Chunk* getChunkByBlock(int x, int y, int z);
	//unsigned char getLight(int x, int y, int z, int channel);
	//void set(int x, int y, int z, int id);

	//void write(unsigned char* dest);
	//void read(unsigned char* source);
};

#endif // !CHUNKS_HPP
