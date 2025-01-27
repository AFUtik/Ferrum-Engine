#ifndef TEXTUREATLASGENERATOR_HPP
#define TEXTUREATLASGENERATOR_HPP

#include <vector>

class TextureAtlas;
class TextureManager;

class TextureAtlasGenerator {
private:

public:
    static TextureAtlas* generateTextureAtlas(TextureManager* texture_manager, unsigned int width, unsigned int height, std::vector<size_t> categories);
};

#endif