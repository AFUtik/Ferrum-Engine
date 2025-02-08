#include "TextureManager.hpp"
#include "TextureHandler.hpp"
#include "TextureGLHandler.hpp"
#include "TextureAtlasGenerator.hpp"

#include <map>

TextureManager::TextureManager(std::string resource_loc) : resource_location(resource_loc), texture_location(""), texture_group(nullptr, true) {}

void TextureManager::changeTextureLocation(std::string location) {
    texture_location = location;
}

const TextureMap& TextureManager::getTextureMap() {
    return texture_m;
}

TextureAtlas* TextureManager::getAtlas(size_t location) {
    return atlas_m[location].get();
}

Texture* TextureManager::getTexture(size_t location) {
    return texture_m[location].get();
}

const std::vector<size_t>& TextureManager::getTexturesByGroup(std::string group_tag) {
    return texture_group.findOrCreateGroup(group_tag)->getObjects();
}

void TextureManager::loadBunchToGroup(std::string group_tag, size_t tex_loc, const std::vector<std::string> &paths) {
    TagGroup<size_t>* group = texture_group.findOrCreateGroup(group_tag);
    for(const std::string path : paths) {
        group->addObject(tex_loc);
        loadTexture(tex_loc, path);
        tex_loc++;
    }
}

void TextureManager::loadTextureToGroup(std::string group_tag, size_t tex_loc, std::string texture_name) {
    texture_group.findOrCreateGroup(group_tag)->addObject(tex_loc);
    loadTexture(tex_loc, texture_name);
}

void TextureManager::loadTexture(size_t location, const std::string &path) {
    Texture *texture = load_texture_png(resource_location+texture_location+path);
    if(texture != nullptr) texture_m[location] = std::unique_ptr<Texture>(texture);
}

void TextureManager::loadAtlasByGroup(size_t location, std::string tag) {
    loadAtlasByTex(location, texture_group.findOrCreateGroup(tag)->getObjects());
}

void TextureManager::loadAtlasByTex(size_t location, const std::vector<size_t> &tex_locs) {
    std::map<size_t, Texture*> textures;
    for(const size_t &loc : tex_locs) {
        textures.emplace(loc, texture_m[loc].get());
    }
    TextureAtlas* texture_atlas = TextureAtlasGenerator::generateTextureAtlas(textures);
    if(texture_atlas != nullptr) atlas_m[location] = std::unique_ptr<TextureAtlas>(texture_atlas);
}

void TextureManager::clearTextures() {
    cleared = true;
    texture_m.clear();
}