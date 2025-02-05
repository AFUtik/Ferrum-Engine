#include "TextureManager.hpp"
#include "TextureHandler.hpp"
#include "TextureGLHandler.hpp"
#include "TextureAtlasGenerator.hpp"



TextureManager::TextureManager(std::string resource_loc) : resource_location(resource_loc), texture_location("") {}

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
    return texture_group.findGroup(group_tag).locations;
}

void TextureManager::loadBunchToGroup(std::string group_tag, size_t tex_loc, const std::vector<std::string> &paths) {
    const TextureGroup& group = texture_group.findGroup(group_tag);
    for(const std::string path : paths) {
        group.loadLocation(tex_loc);
        loadTexture(tex_loc, path);
        tex_loc++;
    }
}

void TextureManager::loadTextureToGroup(std::string group_tag, size_t tex_loc, std::string texture_name) {
    texture_group.findGroup(group_tag).loadLocation(tex_loc);
    loadTexture(tex_loc, texture_name);
}

void TextureManager::loadTexture(size_t location, const std::string &path) {
    Texture *texture = load_texture_png(resource_location+texture_location+path);
    if(texture != nullptr) texture_m[location] = std::unique_ptr<Texture>(texture);
}

void TextureManager::loadAtlasByGroups(size_t location, std::vector<std::string> group_tags) {
    std::vector<size_t> common_group;
    for(const std::string &tag : group_tags) {
        const std::vector<size_t> &locations = texture_group.findGroup(tag).locations;
        common_group.insert(common_group.end(), locations.begin(), locations.end());
    }
    TextureAtlas* texture_atlas = TextureAtlasGenerator::generateTextureAtlas(texture_m, common_group);
    if(texture_atlas != nullptr) atlas_m[location] = std::unique_ptr<TextureAtlas>(texture_atlas);
}

void TextureManager::loadAtlasByTex(size_t location, std::vector<size_t> tex_locs) {
    TextureAtlas* texture_atlas = TextureAtlasGenerator::generateTextureAtlas(texture_m, tex_locs);
    if(texture_atlas != nullptr) atlas_m[location] = std::unique_ptr<TextureAtlas>(texture_atlas);
}

void TextureManager::clearTextures() {
    cleared = true;
    texture_m.clear();
}