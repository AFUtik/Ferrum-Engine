#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

class Texture {
public:
	unsigned int success;
	unsigned char* image_data;
	int width, height;

	Texture(unsigned int success, int width, int height, unsigned char* image_data);
	~Texture();

	void flipImageVertically();
	void bind();
};

#endif // !TEXTURE_HPP
