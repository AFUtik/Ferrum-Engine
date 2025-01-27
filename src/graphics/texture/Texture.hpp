#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

class Texture {
public:
	unsigned char* image_data;
	int width, height;
	bool loaded;

	Texture(bool loaded, int width, int height, unsigned char* image_data);
	~Texture();

	void flipImageVertically();
};

#endif // !TEXTURE_HPP
