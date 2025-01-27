#include "Texture.hpp"
#include "TextureGLBinder.hpp"

#include <GLFW/glfw3.h>	

void TextureGLBinder::createTexture(Texture* texture) {
    glGenTextures(1, &texture->gl_id);
    glBindTexture(GL_TEXTURE_2D, texture->gl_id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, alpha, GL_UNSIGNED_BYTE, (GLvoid*)*image_data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
}