#include "TextureAtlasGenerator.hpp"

#include "Texture.hpp"
#include "TextureHandler.hpp"

static const unsigned int channels = 4;

void TextureAtlasGenerator::pushIntoBuffer(uint32_t x, uint32_t y, uint32_t width, uint32_t height, int32_t padding, 
                                           uint8_t* raw_data,
                                           uint32_t buffer_width, uint32_t buffer_height,
                                           uint8_t* buffer) {
    unsigned int row_size = width * channels;
    uint8_t* cur_buffer = buffer+(y*channels*buffer_width)+(x*channels);
    int cur_padding = 0;

    for(int _y = 0; _y < (height+padding); ++_y) {
        uint8_t* cur_row = raw_data + (_y-cur_padding) * row_size;
        memcpy(cur_buffer+(_y*channels*buffer_width), cur_row, padding*channels);
        memcpy(cur_buffer+(_y*channels*buffer_width)+(padding*channels), cur_row, row_size);
        if(cur_padding < padding) cur_padding++;
    }
}

Texture* TextureAtlasGenerator::generateTextureAtlas(std::vector<std::pair<TexturePos, TextureEntry*>> &textures,
                                                     uint32_t atlas_width, uint32_t atlas_height, uint32_t padding) {
    unsigned char* buffer = new unsigned char[atlas_width*channels*atlas_height];
    for(auto& tex_data : textures) {
        Texture* texture = tex_data.second->second;
        pushIntoBuffer(tex_data.first.x, tex_data.first.y, texture->width, texture->height, padding, texture->image_data, 
                       atlas_width, atlas_height, buffer);
    }
    Texture* texture = new Texture(true, atlas_width, atlas_height, buffer);
    save_texture_png("E:/Cpp/FerrumEngine/resources/textures/atlases/atlas.png", texture);
    return texture;
}