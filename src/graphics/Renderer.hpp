#ifndef RENDERER_HPP
#define RENDERER_HPP

class Mesh;
class Chunk2d;

class Renderer {
	size_t capacity;
	float* buffer;
public:
	
	Renderer(size_t capacity);
	~Renderer();

	void render_chunk2d(Chunk2d* chunk, const Chunk2d** chunks); // Generates Mesh and sets it in chunk class. //
};

#endif 