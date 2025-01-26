#ifndef MESH_HPP
#define MESH_HPP

#define PLANE 6
#define CUBE 36

#include <stdlib.h>

class Mesh {
private:
	unsigned int vao;
	unsigned int vbo;
	size_t vertices;
	int* attrs;
	int vertex_size;
	float* buffer;
	int index;
public:
	Mesh(size_t vertices, int* attrs);
	~Mesh();

	void add_vertex(float x, float y, float z, float u, float v);
	void generate();
	void draw(unsigned int primitive);
};

#endif /* GRAPHICS_MESH_H_ */