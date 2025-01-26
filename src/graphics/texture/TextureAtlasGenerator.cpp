#include "TextureManager.hpp"
#include "TextureAtlasGenerator.hpp"
#include "TextureAtlas.hpp"
#include "Texture.hpp"

TextureAtlas* TextureAtlasGenerator::generateTextureAtlas(unsigned int width, unsigned int height, std::set<size_t> categories) {
    const TextureMap& tex_map = texture_manager->getTextureMap();

    unsigned char* buffer = new unsigned char[width*4*height]; // 4 channels //
    unsigned int offset_x = 0, offset_y = 0;
    for(size_t category : categories) {
        for(auto&& [loc, tex] : tex_map.at(category)) {
            unsigned int row_size = tex->width * 4;
            unsigned char* cur_buffer = buffer+(offset_y*4*width)+(offset_x*4);
            for(int y = 0; y < tex->height; ++y) {
                unsigned char* cur_row = tex->image_data + y * row_size;

                memcpy(buffer+(y*4*width), cur_row, row_size);
            }
            offset_x += tex->width;
            if(offset_x >= width) {
                offset_x -= width;
                offset_y += tex->height;
            }
        }
    }
    Texture* atlas = new Texture(true, width, height, buffer);
    return nullptr;
}