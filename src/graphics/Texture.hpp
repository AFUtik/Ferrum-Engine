#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

class Texture {
public:
	unsigned int id;
	int width, height;
	Texture(unsigned int id, int width, int height);
	~Texture();

	void bind();
};

#endif // !TEXTURE_HPP
