#include "TileMapper.hpp"
#include "Tilemap.hpp"

#include "../algorithms/Guillotine.hpp"

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

Tilemap* TileMapper::generateTilemap(const Atlas &atlas) {
    Tilemap *tilemap = new Tilemap(atlas.texture);
    std::vector<TextureEntry> entries;
    const uint32_t channels = 4;
    
    Texture* atlas_texture = atlas.texture;
    uint8_t* image_data = atlas_texture->image_data;
    int i = 0;
    const uint32_t tilesize_y = atlas_texture->height/atlas.tile_height;
    const uint32_t tilesize_x = atlas_texture->width/atlas.tile_width;
    for(int y = 0; y < tilesize_y; y++) {
        uint8_t* cur_data = image_data + (y*atlas.tile_height*atlas_texture->width*channels);
        for(int x = 0; x < tilesize_x; x++) {
            Texture* texture = new Texture(
                true, 
                atlas.tile_width, 
                atlas.tile_height, 
                cur_data + (x*atlas.tile_width*channels)
            );
            texture->delete_data = false;

            TextureEntry entry(atlas.name + std::to_string(i), texture);
            entry.x_offset = atlas_texture->width;

            entries.push_back(entry);
            i++;
            if(i==atlas.tile_amount) {
                return generateTilemap(entries);
            }
        }    
    } 
    return generateTilemap(entries);
}

Tilemap* TileMapper::generateTilemap(const std::vector<Atlas> &atlases) {
    std::vector<TextureEntry> entries;
    const uint32_t channels = 4;
    for(const Atlas &atlas : atlases) {
        Texture* atlas_texture = atlas.texture;
        uint8_t* image_data = atlas_texture->image_data;
        int i = 0;
        const uint32_t tilesize_y = atlas_texture->height/atlas.tile_height;
        const uint32_t tilesize_x = atlas_texture->width/atlas.tile_width;
        for(int y = 0; y < tilesize_y; y++) {
            uint8_t* cur_data = image_data + (y*atlas.tile_height*atlas_texture->width*channels);
            for(int x = 0; x < tilesize_x; x++) {
                Texture* texture = new Texture(
                    true, 
                    atlas.tile_width, 
                    atlas.tile_height, 
                    cur_data + (x*atlas.tile_width*channels)
                );
                texture->delete_data = false;

                TextureEntry entry(atlas.name + std::to_string(i), texture);
                entry.x_offset = atlas_texture->width;

                entries.push_back(entry);
                i++;
                if(i==atlas.tile_amount) {
                    return generateDynamicTilemap(entries);
                }
            }    
        } 
    }
    return generateDynamicTilemap(entries);
}

Tilemap* TileMapper::generateTilemap(std::vector<TextureEntry> &entries) {
    unsigned int atlas_size = min_texture_size;
    unsigned int texture_amount = entries.size();
    unsigned int texture_width = entries.front().texture->width+padding; 
    unsigned int texture_height = entries.front().texture->height+padding;
    while ((1 + texture_amount / (atlas_size / texture_width)) * texture_width > atlas_size) {
        atlas_size *= 2;
        if (atlas_size > max_texture_size) {
            std::cerr << "Error: Atlas size exceeds max texture size!" << std::endl;
            return nullptr;
        }
    }
    std::vector<std::pair<TexturePos, TextureEntry*>> tiles;
    tiles.reserve(texture_amount);
    unsigned int x = 0;
    unsigned int y = 0;
    for (TextureEntry &entry : entries) {
        if(texture_width-padding!=entry.texture->width || texture_height-padding!=entry.texture->height) {
            std::cerr << "Error: Failed to generate tilemap. Different texture sizes." <<
                          "Please use DynamicTilemap for different sizes." << std::endl;
            return nullptr;
        }
        if (x + texture_width >= atlas_size) {
            x = 0;
            y += texture_height; 
        }
        tiles.emplace_back(TexturePos(x, y, texture_width, texture_height), &entry);
        x += texture_width;
    }
    int i = 0;
    Texture* texture = TextureAtlasGenerator::generateTextureAtlas(tiles, atlas_size, atlas_size, padding);
    Tilemap* tilemap = new Tilemap(texture);
    for(auto& tile : tiles) {
        TexturePos& tex_pos = tile.first;
        TextureRegion* region = TileMapper::createTextureRegion(
            tex_pos.x, 
            tex_pos.y,
            tex_pos.width, 
            tex_pos.height, 
            padding, atlas_size, atlas_size
        );
        tilemap->loadTextureRegion(tile.second->name, region);
    }
    return tilemap;
}

Tilemap* TileMapper::generateDynamicTilemap(std::vector<TextureEntry> &entries) {
    GuillotinePacker packer(min_texture_size, min_texture_size);
    std::vector<std::pair<TexturePos, TextureEntry*>> tiles;
    tiles.reserve(entries.size());

    for (TextureEntry &pair : entries) {
        tiles.emplace_back(Rectangle(0, 0, pair.texture->width + padding, pair.texture->height + padding), &pair);
    }
    std::sort(tiles.begin(), tiles.end(), [](const auto& a, const auto& b) {
        return a.first.width * a.first.height > b.first.width * b.first.height;
    });
    int i = 0;
    while(i < tiles.size()) {
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
    for(int i = 0; i < tiles.size(); i++) {
        std::cout << tiles[i].first.width << " " << tiles[i].first.height << tiles[i].first.x << " " << tiles[i].first.y << std::endl;
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
        tilemap->loadTextureRegion(tile.second->name, region);
    }
    return tilemap;
}