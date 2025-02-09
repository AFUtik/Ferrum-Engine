#include "Tilemap.hpp"

void Tilemap::loadTextureRegion(std::string location, TextureRegion* region) {
    size_t size = regions.size();
    regions_map[location] = std::unique_ptr<TextureRegion>(region);
    regions_pos[location] = size; 
    regions.push_back(region);
}

const size_t& Tilemap::getTextureRegionPos(const std::string &location) {
    return regions_pos[location];
}

TextureRegion* Tilemap::getTextureRegion(const size_t &index) {
    return regions[index];
}

TextureRegion* Tilemap::getTextureRegion(const std::string &location) {
    return regions_map[location].get();
}
