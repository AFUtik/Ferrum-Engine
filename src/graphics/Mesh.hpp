#ifndef MESH_HPP
#define MESH_HPP

#include <stdlib.h>

class Mesh {
private:
	unsigned int vao;
	unsigned int vbo;
	size_t vertices;
public:
	Mesh(const float* buffer, size_t vertices, const int* attrs);
	~Mesh();

	void draw(unsigned int primitive);
};

#endif /* GRAPHICS_MESH_H_ */