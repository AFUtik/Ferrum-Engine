#include "GLTexture.hpp"
#include "Texture.hpp"
#include "TextureGLHandler.hpp"

#include <GL/glew.h>	
#include <GLFW/glfw3.h>	


GLTexture* TextureGLHandler::createTexture(Texture* texture) {
    GLTexture* gl_texture = new GLTexture();

    glGenTextures(1, &gl_texture->texture_id);
    glBindTexture(GL_TEXTURE_2D, gl_texture->texture_id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)texture->image_data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);

    return gl_texture;
}