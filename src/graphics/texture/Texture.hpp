#ifndef TEXTURE_HPP
#define TEXTURE_HPP

class Texture {
public:
	unsigned char* image_data;
	unsigned int width, height;
	bool loaded;
	bool delete_data = true;

	Texture(bool loaded, int width, int height, unsigned char* image_data);
	~Texture();

	void flipImageVertically();
};

#endif // !TEXTURE_HPP
