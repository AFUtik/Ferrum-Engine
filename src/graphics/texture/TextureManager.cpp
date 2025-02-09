#include "TextureManager.hpp"
#include "TextureHandler.hpp"
#include "TextureGLHandler.hpp"
#include "TileMapper.hpp"

#include <iostream>

TextureManager::TextureManager(std::string resource_loc) : resource_location(resource_loc), texture_location(""), texture_group(nullptr, true) {}

void TextureManager::changeTextureLocation(std::string location) {
    texture_location = location;
}

Tilemap* TextureManager::getTilemap(std::string location) {
    return tilemap_m[location].get();
}

Texture* TextureManager::getTexture(std::string location) {
    return texture_m[location].get();
}

const std::vector<std::string>& TextureManager::getTexturesByGroup(std::string group_tag) {
    return texture_group.findOrCreateGroup(group_tag)->getObjects();
}

void TextureManager::loadBunchToGroup(std::string group_tag, std::string tex_loc, const std::vector<std::string> &paths) {
    TagGroup<std::string>* group = texture_group.findOrCreateGroup(group_tag);
    int index = 0;
    for(const std::string &path : paths) {
        std::string new_loc = tex_loc + std::to_string(index);
        group->addObject(new_loc);
        loadTexture(new_loc, path);
        index++;
    }
}

void TextureManager::loadTextureToGroup(std::string group_tag, std::string tex_loc, std::string texture_name) {
    texture_group.findOrCreateGroup(group_tag)->addObject(tex_loc);
    loadTexture(tex_loc, texture_name);
}

void TextureManager::loadTexture(std::string location, const std::string &path) {
    Texture *texture = load_texture_png(resource_location+texture_location+path);
    if(texture != nullptr) texture_m[location] = std::unique_ptr<Texture>(texture);
}

void TextureManager::loadTilemapByGroup(std::string location, std::string tag) {
    loadTilemapByTex(location, texture_group.findOrCreateGroup(tag)->getObjects());
}

void TextureManager::loadTilemapByTex(std::string tilemap_loc, const std::vector<std::string> &tex_locs) {
    std::vector<std::pair<std::string, Texture*>> textures;
    textures.reserve(tex_locs.size());
    for(const std::string &loc : tex_locs) {
        textures.emplace_back(loc, texture_m[loc].get());
    }
    Tilemap* tilemap = TileMapper::generateTilemap(textures);
    if(tilemap != nullptr) tilemap_m[tilemap_loc] = std::unique_ptr<Tilemap>(tilemap);
}

void TextureManager::clearTextures() {
    texture_m.clear();
}