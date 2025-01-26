#ifndef TEXTUREATLASGENERATOR_HPP
#define TEXTUREATLASGENERATOR_HPP

#include <set>

class TextureAtlas;
class TextureManager;

class TextureAtlasGenerator {
private:
    TextureManager* texture_manager;
public:
    TextureAtlasGenerator(TextureManager* texture_manager);

    TextureAtlas* generateTextureAtlas(unsigned int width, unsigned int height, std::set<size_t> categories);
};

#endif