#include "TextureAtlasGenerator.hpp"
#include "TextureHandler.hpp"

#include "../../algorithms/Guillotine.hpp"
#include <algorithm>

//#include <iostream>

TextureAtlas* TextureAtlasGenerator::generateTextureAtlas(TextureMap &tex_map, const std::set<size_t> &tex_locs) {
    GuillotinePacker packer(MIN_WIDTH, MIN_HEIGHT);
    std::vector<Rectangle> tiles;
    unsigned int padding = 1;
    unsigned int channels = 4;
    for(const size_t &loc : tex_locs) {
        Texture* tex = tex_map.at(loc).get();
        Rectangle rectangle(0, 0, tex->width+padding, tex->height+padding);
        rectangle.data = loc;
        auto it = std::lower_bound(tiles.begin(), tiles.end(), rectangle, [](const Rectangle& a, const Rectangle& b) {
            return a.width * a.height > b.width * b.height;
        });
        tiles.insert(it, rectangle);
    }
    for(int i = 0; i < tiles.size();) {
        if (!packer.pack(tiles[i])) {
            packer = GuillotinePacker(packer.getAtlasWidth() * 2, packer.getAtlasHeight() * 2);
            i = 0;
        } else i++;
    }
    int width = packer.getAtlasWidth();
    int height = packer.getAtlasHeight();

    TextureAtlas* texture_atlas = new TextureAtlas(nullptr);
    unsigned char* buffer = new unsigned char[width*channels*height];
    for(Rectangle &rect : tiles) {
        Texture* tex = tex_map.at(rect.data).get();
        TextureAtlasPos* atlas_pos = new TextureAtlasPos();
        
        float padding_uvsize_u = padding / (float)width;
        float padding_uvsize_v = padding / (float)height;
        atlas_pos->u1 = padding_uvsize_u + (float)rect.x / (float)width;
        atlas_pos->v1 = padding_uvsize_v + (float)rect.y / (float)width;
        atlas_pos->u2 = atlas_pos->u1 + ((float)rect.width / (float)width) - padding_uvsize_u;
        atlas_pos->v2 = atlas_pos->v1 + ((float)rect.height/ (float)height) - padding_uvsize_v;
        texture_atlas->atlas_pos_m[rect.data] = std::unique_ptr<TextureAtlasPos>(atlas_pos);

        unsigned int row_size = tex->width * channels;
        unsigned char* cur_buffer = buffer+(rect.y*channels*width)+(rect.x*channels);
        int cur_padding = 0;
        for(int y = 0; y < (tex->height+padding); ++y) {
            unsigned char* cur_row = tex->image_data + (y-cur_padding) * row_size;
            memcpy(cur_buffer+(y*channels*width), cur_row, padding*channels);
            memcpy(cur_buffer+(y*channels*width)+(padding*channels), cur_row, row_size);

            if(cur_padding < padding) cur_padding++;
        }
    }
    texture_atlas->texture = new Texture(true, width, height, buffer);
    save_texture_png("E:/Cpp/FerrumEngine/resources/textures/atlases/atlas.png", texture_atlas->texture);
    return texture_atlas;
}