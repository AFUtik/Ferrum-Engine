#ifndef TEXTUREATLASGENERATOR_HPP
#define TEXTUREATLASGENERATOR_HPP

#include "../../structures/Rectangle.hpp"
#include "Texture.hpp"

#include <vector>
#include <map>

class Tilemap;
class TextureAtlas;
class TextureAtlasPos;

class TextureAtlasGenerator {
private:
    static void pushIntoBuffer(uint32_t x, uint32_t y, uint32_t width, uint32_t height, int32_t padding, 
                               uint8_t* raw_data,
                               uint32_t buffer_width, uint32_t buffer_height,
                               uint8_t* buffer);
public:
    static Texture* generateTextureAtlas(std::vector<std::pair<std::string, Rectangle>> &positions, const std::map<std::string, Texture*> &textures,
                                         uint32_t atlas_width, uint32_t atlas_height, uint32_t padding);
};

#endif