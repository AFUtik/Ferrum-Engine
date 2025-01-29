#include "TextureManager.hpp"
#include "TextureAtlasGenerator.hpp"
#include "TextureAtlas.hpp"
#include "Texture.hpp"

#include <memory>

TextureAtlas* TextureAtlasGenerator::generateTextureAtlas(TextureManager* texture_manager, unsigned int width, unsigned int height, std::vector<size_t> categories) {
    const TextureMap& tex_map = texture_manager->getTextureMap();
    TextureAtlas* texture_atlas = new TextureAtlas(nullptr);

    unsigned char* buffer = new unsigned char[width*4*height]; // 4 channels //
    unsigned int offset_x = 0, offset_y = 0;
    int id = 0;
    for(size_t category : categories) {
        Texture* tex = tex_map.at(category).get();
        TextureAtlasPos* atlas_pos = new TextureAtlasPos();
        
        int tilesize = width / tex->width;
        float uvsize = 1.0f / (float)tilesize;
        atlas_pos->u1 = (id % tilesize) * uvsize;
        atlas_pos->v1 = (1 + static_cast<float>(id) / static_cast<float>(tilesize)) * uvsize;
        atlas_pos->u2 = atlas_pos->u1 + uvsize;
        atlas_pos->v2 = atlas_pos->v1 + uvsize;
        texture_atlas->atlas_pos_m[category] = std::unique_ptr<TextureAtlasPos>(atlas_pos);

        unsigned int row_size = tex->width * 4;
        unsigned char* cur_buffer = buffer+(offset_y*4*width)+(offset_x*4);
        for(int y = 0; y < tex->height; ++y) {
            unsigned char* cur_row = tex->image_data + y * row_size;
            memcpy(cur_buffer+(y*4*width), cur_row, row_size);
        }
        offset_x += tex->width;
        if(offset_x >= width) {
            offset_x -= width;
            offset_y += tex->height;
        }
    }
    texture_atlas->texture = new Texture(true, width, height, buffer);
    return texture_atlas;
}