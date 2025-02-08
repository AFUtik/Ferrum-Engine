#include "TileMapper.hpp"
#include "Tilemap.hpp"
#include "Texture.hpp"

#include "TextureAtlasGenerator.hpp"
#include "../../algorithms/Guillotine.hpp"

#include <algorithm>
#include <iostream>

unsigned int TileMapper::padding = 0;
unsigned int TileMapper::max_texture_size = 0;
unsigned int TileMapper::min_texture_size = 0;

TextureRegion* createTextureRegion(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t padding, 
                                   uint32_t buffer_width, uint32_t buffer_height) {
    TextureRegion* region = new TextureRegion();
    float padding_uvsize_u = padding / (float)buffer_width;
    float padding_uvsize_v = padding / (float)buffer_height;
    region->orig_u1 = (float)x / (float)buffer_width;
    region->orig_v1 = (float)y / (float)buffer_width;
    region->u1 = padding_uvsize_u + region->orig_u1;
    region->v1 = padding_uvsize_v + region->orig_v1;
    region->u2 = region->u1 + ((float)width / (float)buffer_width) - padding_uvsize_u;
    region->v2 = region->v1 + ((float)height/ (float)buffer_height) - padding_uvsize_v;
    return region;
}

Tilemap* TileMapper::generateTilemap(const std::vector<std::pair<std::string, Texture*>> &textures) {
    unsigned int atlas_size = min_texture_size*min_texture_size;
    unsigned int texture_amount = textures.size();
    unsigned int texture_width = textures.begin()->second->width; 
    unsigned int texture_height = textures.begin()->second->height; 
    while(atlas_size < texture_width*texture_height*texture_amount) atlas_size*=2;
    
    std::vector<std::pair<std::string, Rectangle>> tiles;
    for (auto&& [id, unique_ptr] : textures) {
        if(texture_width!=unique_ptr->width || texture_height!=unique_ptr->height) {
            std::cerr << "Error: Failed to generate tilemap. Different texture sizes." <<
                          "Please use DynamicTilemap for different sizes." << std::endl;
            return nullptr;
        }
        tiles.emplace_back(id, Rectangle(0, 0, unique_ptr->width + padding, unique_ptr->height + padding));
    }
    Texture* texture = TextureAtlasGenerator::generateTextureAtlas(tiles, textures, atlas_size, atlas_size, padding);
    Tilemap* tilemap = new Tilemap(texture);
    for(std::pair<std::string, Rectangle> &tile : tiles) {
        TextureRegion* region = TileMapper::createTextureRegion(
            tile.second.x, 
            tile.second.y,
            tile.second.width, 
            tile.second.height, 
            padding, atlas_size, atlas_size
        );
        tilemap->loadTextureRegion(tile.first, region);
    }
    return tilemap;
}

Tilemap* TileMapper::generateDynamicTilemap(const std::map<std::string, Texture*> &textures) {
    GuillotinePacker packer(min_texture_size, min_texture_size);
    std::vector<std::pair<std::string, Rectangle>> tiles;
    for (auto&& [id, unique_ptr] : textures) {
        tiles.emplace_back(id, Rectangle(0, 0, unique_ptr->width + padding, unique_ptr->height + padding));
    }
    std::sort(tiles.begin(), tiles.end(), [](const auto& a, const auto& b) {
        return a.second.width * a.second.height > b.second.width * b.second.height;
    });
    for(int i = 0; i < tiles.size();) {
        if (!packer.pack(tiles[i].second)) {
            int exhanced_width = packer.getAtlasWidth() * 2;
            int exhanced_height = packer.getAtlasHeight() * 2;
            if(exhanced_width > max_texture_size) {
                std::cerr << "Error: Failed to generate tilemap. The size limits of an atlas that supports opengl were exceed. " << std::endl;
                return nullptr;
            }
            packer = GuillotinePacker(exhanced_width, exhanced_height);
            i = 0;
        } else i++;
    }
    int width = packer.getAtlasWidth(), height = packer.getAtlasHeight();
    Texture* texture = TextureAtlasGenerator::generateTextureAtlas(tiles, textures, width, height, padding);
    Tilemap* tilemap = new Tilemap(texture);
    for(std::pair<std::string, Rectangle> &tile : tiles) {
        TextureRegion* region = TileMapper::createTextureRegion(
            tile.second.x, 
            tile.second.y,
            tile.second.width, 
            tile.second.height, 
            padding, width, height
        );
        tilemap->loadTextureRegion(tile.first, region);
    }
    return tilemap;
}