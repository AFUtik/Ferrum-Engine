#include "TextureAtlas.hpp"
#include "Texture.hpp"

#include <GL/glew.h>

TextureAtlasPos* TextureAtlas::getAtlasPos(size_t location) {
    return atlas_pos_m[location].get();
}

Texture* TextureAtlas::getTexture() {
    return texture;
}

TextureAtlas::~TextureAtlas() {
    delete texture;
}