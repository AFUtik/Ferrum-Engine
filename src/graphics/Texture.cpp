#include "Texture.hpp"

#include "GL/glew.h"

Texture::Texture(unsigned int id, int width, int height) : id(id), width(width), height(height) {}

void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, id);
}

Texture::~Texture() {
	glDeleteTextures(1, &id);
}
