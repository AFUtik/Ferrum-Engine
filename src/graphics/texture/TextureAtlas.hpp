#ifndef TEXTUREATLAS_HPP
#define TEXTUREATLAS_HPP

#include <unordered_map>
#include <memory>

#include "TextureAtlasPos.hpp"

class Texture;

class TextureAtlas {
private:
    std::unordered_map<size_t, std::unique_ptr<TextureAtlasPos>> atlas_pos_m;
    Texture* texture;

    friend class TextureAtlasGenerator;
public:
    TextureAtlas(Texture* texture) : texture(texture) {};
    ~TextureAtlas();

    TextureAtlasPos* getAtlasPos(size_t location);
    Texture* getTexture();
};

#endif