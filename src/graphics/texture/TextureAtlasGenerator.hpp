#ifndef TEXTUREATLASGENERATOR_HPP
#define TEXTUREATLASGENERATOR_HPP

#define MIN_HEIGHT 128
#define MIN_WIDTH 128

#define MAX_HEIGHT 4096
#define MAX_WIDTH 4096

#include <set>
#include "TextureManager.hpp"

class TextureAtlas;

class TextureAtlasGenerator {
private:

public:
    static TextureAtlas* generateTextureAtlas(TextureMap &tex_map, const std::set<size_t> &categories);
};

#endif