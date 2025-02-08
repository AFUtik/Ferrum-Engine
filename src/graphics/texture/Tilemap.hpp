#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <string>
#include <unordered_map>
#include <memory>

#include "Texture.hpp"
#include "TextureRegion.hpp"

class Texture;

class Tilemap {
private:
    std::unordered_map<std::string, std::unique_ptr<TextureRegion>> regions_map;
    std::vector<TextureRegion*> regions;

    std::unique_ptr<Texture> atlas_texture;

    unsigned int tile_width;
    unsigned int tile_height;
public:
    Tilemap(Texture* texture) : atlas_texture(texture) {}

    inline void loadTextureRegion(std::string location, TextureRegion* region) {
        regions_map[location] = std::unique_ptr<TextureRegion>(region);
        regions.push_back(region);
    }

    inline TextureRegion* getTextureRegion(const size_t &index) {
        return regions[index];
    }

    inline TextureRegion* getTextureRegion(const std::string &location) {
        return regions_map[location].get();
    }

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