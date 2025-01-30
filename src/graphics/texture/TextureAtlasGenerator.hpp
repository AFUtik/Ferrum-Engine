#ifndef TEXTUREATLASGENERATOR_HPP
#define TEXTUREATLASGENERATOR_HPP

#include <set>

#include "TextureManager.hpp"

class TextureAtlas;

class TextureAtlasGenerator {
private:

public:
    static TextureAtlas* generateTextureAtlas(TextureMap &tex_map, unsigned int width, unsigned int height, const std::set<size_t> &categories);
};

#endif