#include "TextureAtlas.hpp"
#include "Texture.hpp"

#include <GL/glew.h>

Texture* TextureAtlas::getTexture() {
    return texture;
}

TextureAtlas::~TextureAtlas() {
    delete texture;
}