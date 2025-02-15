#include "TextureAtlasGenerator.hpp"

#include "../../graphics/texture/Texture.hpp"
#include "../../graphics/texture/TextureHandler.hpp"

#include <iostream>

bool TextureAtlasGenerator::save_atlas = false;
std::string TextureAtlasGenerator::path;

static const unsigned int channels = 4;

TextureEntry::TextureEntry(std::string name, Texture* texture) : name(name), texture(texture), x_offset(texture->width),  y_offset(texture->height) {}

Texture* TextureAtlasGenerator::generateTextureAtlas(std::vector<std::pair<TexturePos, TextureEntry*>> &textures,
                                                     uint32_t atlas_width, uint32_t atlas_height, uint32_t padding) {


    uint8_t* buffer = new uint8_t[atlas_width*channels*atlas_height];
    for(auto&& [pos, entry] : textures) {
        Texture* texture = entry->texture;
        
        uint8_t *raw_data = texture->image_data;
        const uint32_t row_size = texture->width * channels;
        const uint32_t offset_size_x = entry->x_offset*channels;

        uint8_t* cur_buffer = buffer+(pos.y*channels*atlas_width)+(pos.x*channels);
        int32_t cur_padding = 0;

        for(int _y = 0; _y < (texture->height+padding); ++_y) {
            uint8_t* cur_row = raw_data + (_y-cur_padding) * offset_size_x;
 
            memcpy(cur_buffer+(_y*channels*atlas_width), cur_row, padding*channels);
            memcpy(cur_buffer+(_y*channels*atlas_width)+(padding*channels), cur_row, row_size);
            if(cur_padding < padding) cur_padding++;
        }
    }
    Texture* texture = new Texture(true, atlas_width, atlas_height, buffer);
    if(save_atlas==true) {
        std::string name = textures.front().second->name;
        name.pop_back();
        save_texture_png(path + name, texture);
    }
    return texture;
}