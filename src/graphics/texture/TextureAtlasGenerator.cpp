#include "TextureAtlasGenerator.hpp"
#include "TextureHandler.hpp"

TextureAtlas* TextureAtlasGenerator::generateTextureAtlas(TextureMap& tex_map, unsigned int width, unsigned int height, const std::set<size_t> &categories) {
    TextureAtlas* texture_atlas = new TextureAtlas(nullptr);

    unsigned int padding = 1;
    unsigned char* buffer = new unsigned char[width*4*height]; // 4 channels //
    unsigned int offset_x = 0, offset_y = 0;
    int id = 0;
    for(size_t category : categories) {
        Texture* tex = tex_map.at(category).get();
        TextureAtlasPos* atlas_pos = new TextureAtlasPos();
        
        int tilesize = width / (tex->width);
        float padding_uvsize_u = 1.0f / (float)width * (id+1);
        float padding_uvsize_v = 1.0f / (float)width * (id % tilesize);
        float uvsize = 1.0f / (float)tilesize;
        atlas_pos->u1 = padding_uvsize_u + (id % tilesize) * uvsize;
        atlas_pos->v1 = id / tilesize * uvsize;
        atlas_pos->u2 = atlas_pos->u1 + uvsize;
        atlas_pos->v2 = atlas_pos->v1 + uvsize;
        texture_atlas->atlas_pos_m[category] = std::unique_ptr<TextureAtlasPos>(atlas_pos);

        unsigned int row_size = tex->width * 4;
        unsigned char* cur_buffer = buffer+(offset_y*4*width)+(offset_x*4);
        int cur_padding = 0;
        for(int y = 0; y < (tex->height+padding); ++y) {
            unsigned char* cur_row = tex->image_data + (y-cur_padding) * row_size;
            memcpy(cur_buffer+(y*4*width), cur_row, padding*4);
            memcpy(cur_buffer+(y*4*width)+(padding*4), cur_row, row_size);

            if(y==tex->height-1) cur_padding++;
        }
        offset_x += tex->width+padding;
        if(offset_x >= width) {
            offset_x -= width;
            offset_y += (tex->height+padding);
        }
        id++;
    }
    texture_atlas->texture = new Texture(true, width, height, buffer);
    save_texture_png("E:/Cpp/FerrumEngine/resources/textures/atlases/atlas.png", texture_atlas->texture);
    return texture_atlas;
}