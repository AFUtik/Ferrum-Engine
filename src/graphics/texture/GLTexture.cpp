#include "GLTexture.hpp"

#include "GL/glew.h"

void GLTexture::bind() {
 	glBindTexture(GL_TEXTURE_2D, texture_id);
}

GLTexture::~GLTexture() {
    glDeleteTextures(1, &texture_id);
}