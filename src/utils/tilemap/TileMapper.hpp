#ifndef TILEMAPMAPPER_HPP
#define TILEMAPMAPPER_HPP

#include "TextureAtlasGenerator.hpp"
#include "Tilemap.hpp"

struct TextureRegion;

class TileMapper {
private:
    static unsigned int padding; /* is used to fix Texture bleeding */
    static unsigned int max_texture_size;
    static unsigned int min_texture_size;

    static TextureRegion* createTextureRegion(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t padding, 
                                                       uint32_t buffer_width, uint32_t buffer_height);
public:
    static inline void usePadding(const unsigned int &new_padding) {padding = new_padding;}
    static inline void setMinSize(const unsigned int &size) {min_texture_size = size;}
    static inline void setMaxSize(const unsigned int &size) {max_texture_size = size;}
    
    static Tilemap* generateTilemap(const std::vector<Atlas> &atlases);
    static Tilemap* generateTilemap(const Atlas &atlas);

    static Tilemap* generateTilemap(std::vector<TextureEntry> &entries);
    static Tilemap* generateDynamicTilemap(std::vector<TextureEntry> &entries); // Creates a tilemap with different sizes of tiles. //
};

#endif