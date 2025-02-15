#ifndef TEXTUREATLASGENERATOR_HPP
#define TEXTUREATLASGENERATOR_HPP

#include "../structures/Rectangle.hpp"

#include <vector>
#include <string>

class Texture;
class Tilemap;

typedef Rectangle TexturePos;

struct TextureEntry {
    std::string name;
    Texture* texture;
    uint32_t x_offset;
    uint32_t y_offset;

    TextureEntry(std::string name, Texture* texture);
};

class TextureAtlasGenerator {
private:
    static bool save_atlas;
    static std::string path;
public:
    inline static void enableAtlasSaving(bool mode) {save_atlas = mode;}
    inline static void setPath(std::string new_path) {
        if(new_path.back() != '/') new_path.push_back('/');
        path = new_path;
    }

    static Texture* generateTextureAtlas(std::vector<std::pair<TexturePos, TextureEntry*>> &textures,
                                         uint32_t atlas_width, uint32_t atlas_height, uint32_t padding);
};

#endif