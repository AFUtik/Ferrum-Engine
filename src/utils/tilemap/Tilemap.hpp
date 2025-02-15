#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <string>
#include <unordered_map>
#include <memory>

#include "../../graphics/texture/Texture.hpp"
#include "../../graphics/texture/TextureRegion.hpp"

struct Atlas {
    std::string name;
    Texture* texture;
    uint32_t tile_width;
    uint32_t tile_height;
    uint32_t tile_amount;

    Atlas(std::string name, uint32_t tile_width, uint32_t tile_height, uint32_t tile_amount) : 
        name(name), tile_width(tile_width), tile_height(tile_height), tile_amount(tile_amount) {}
};

class Tilemap {
private:
    std::unordered_map<std::string, std::unique_ptr<TextureRegion>> regions_map;
    std::unordered_map<std::string, size_t> regions_pos;
    std::vector<TextureRegion*> regions;

    std::unique_ptr<Texture> atlas_texture;

    unsigned int tile_width;
    unsigned int tile_height;
public:
    Tilemap(Texture* texture) : atlas_texture(texture) {}

    void loadTextureRegion(std::string location, TextureRegion* region);

    const size_t& getTextureRegionPos(const std::string &location);

    TextureRegion* getTextureRegion(const size_t &index);

    TextureRegion* getTextureRegion(const std::string &location);

    inline Texture* getAtlasTexture() {
        return atlas_texture.get();
    }

    inline size_t getTilesAmount() {
        return regions.size();
    }

    inline TextureRegion* front() {
        return regions.front();
    }

    inline TextureRegion* back() {
        return regions.back();
    }
};

#endif