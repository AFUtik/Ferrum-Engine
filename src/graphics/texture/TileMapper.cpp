#include "TileMapper.hpp"
#include "Tilemap.hpp"

#include "TextureRegion.hpp"
#include "Texture.hpp"

#include "../../utils/algorithms/Guillotine.hpp"

#include <algorithm>
#include <iostream>

unsigned int TileMapper::padding = 0;
unsigned int TileMapper::max_texture_size = 0;
unsigned int TileMapper::min_texture_size = 0;

TextureRegion* TileMapper::createTextureRegion(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t padding, 
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

Tilemap* TileMapper::generateTilemap(std::vector<TextureEntry> &textures) {
    TextureEntry entry = textures.front();
    unsigned int atlas_size = min_texture_size;
    unsigned int texture_amount = textures.size();
    unsigned int texture_width = textures.front().second->width; 
    unsigned int texture_height = textures.front().second->height;
    while(atlas_size*atlas_size < texture_width*texture_height*texture_amount) atlas_size*=2;
    std::cout << "test tilemap 2 " << atlas_size << std::endl;
    
    std::vector<std::pair<TexturePos, TextureEntry*>> tiles;
    tiles.reserve(texture_amount);
    unsigned int x = 0;
    unsigned int y = 0;
    for (TextureEntry &pair : textures) {
        if(texture_width!=pair.second->width || texture_height!=pair.second->height) {
            std::cerr << "Error: Failed to generate tilemap. Different texture sizes." <<
                          "Please use DynamicTilemap for different sizes." << std::endl;
            return nullptr;
        }
        tiles.emplace_back(TexturePos(x, y, texture_width + padding, texture_height + padding), &pair);
        x+=texture_width+padding;
        if(x>=atlas_size) {
            x = 0;
            y+=texture_height+padding;
        }
    }
    std::cout << "test tilemap 3" << std::endl;
    Texture* texture = TextureAtlasGenerator::generateTextureAtlas(tiles, atlas_size, atlas_size, padding);
    std::cout << "test tilemap 4" << std::endl;
    Tilemap* tilemap = new Tilemap(texture);
    std::cout << "test tilemap 5" << std::endl;
    for(auto& tile : tiles) {
        TexturePos& tex_pos = tile.first;
        TextureRegion* region = TileMapper::createTextureRegion(
            tex_pos.x, 
            tex_pos.y,
            tex_pos.width, 
            tex_pos.height, 
            padding, atlas_size, atlas_size
        );
        tilemap->loadTextureRegion(tile.second->first, region);
    }
    std::cout << "test tilemap 6" << std::endl;
    return tilemap;
}

Tilemap* TileMapper::generateDynamicTilemap(std::vector<TextureEntry> &textures) {
    GuillotinePacker packer(min_texture_size, min_texture_size);
    std::vector<std::pair<TexturePos, TextureEntry*>> tiles;
    tiles.reserve(textures.size());
    for (TextureEntry &pair : textures) {
        tiles.emplace_back(Rectangle(0, 0, pair.second->width + padding, pair.second->height + padding), &pair);
    }
    std::sort(tiles.begin(), tiles.end(), [](const auto& a, const auto& b) {
        return a.first.width * a.first.height > b.first.width * b.first.height;
    });
    for(int i = 0; i < tiles.size();) {
        if (!packer.pack(tiles[i].first)) {
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
    Texture* texture = TextureAtlasGenerator::generateTextureAtlas(tiles, width, height, padding);
    Tilemap* tilemap = new Tilemap(texture);
    for(auto& tile : tiles) {
        TexturePos& tex_pos = tile.first;
        TextureRegion* region = TileMapper::createTextureRegion(
            tex_pos.x, 
            tex_pos.y,
            tex_pos.width, 
            tex_pos.height, 
            padding, width, height
        );
        tilemap->loadTextureRegion(tile.second->first, region);
    }
    return tilemap;
}