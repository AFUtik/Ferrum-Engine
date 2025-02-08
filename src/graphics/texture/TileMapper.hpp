#ifndef TILEMAPMAPPER_HPP
#define TILEMAPMAPPER_HPP

#include <map>
#include <string>

struct TextureRegion;

class Texture;
class Tilemap;

class TileMapper {
private:
    static unsigned int max_texture_size;
    static unsigned int min_texture_size;

    static TextureRegion* createTextureRegion(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t padding, 
                                              uint32_t buffer_width, uint32_t buffer_height);
public:
    static inline void setMinSize(const unsigned int &size) {min_texture_size = size;}
    static inline void setMaxSize(const unsigned int &size) {max_texture_size = size;}

    static Tilemap* generateTilemap(const std::map<std::string, Texture*> &textures);
    static Tilemap* generateDynamicTilemap(const std::map<std::string, Texture*> &textures); // Creates a tilemap with different sizes of tiles. //
};

#endif