#include "TextureManager.hpp"
#include "TextureHandler.hpp"
#include "TextureGLHandler.hpp"
#include "TextureAtlasGenerator.hpp"

TextureManager::TextureManager(std::string resource_loc) : resource_location(resource_loc), texture_location("") {}

void TextureManager::changeTextureLocation(std::string location) {
    texture_location = location;
}

const TextureMap& TextureManager::getTextureMap() {
    return texture_map;
}

GLTexture* TextureManager::getGLTexture(size_t location) {
    return gl_texture_map[location].get();
}

TextureAtlas* TextureManager::getAtlas(size_t location) {
    return atlas_map[location].get();
}

Texture* TextureManager::getTexture(size_t location) {
    return texture_map[location].get();
}

void TextureManager::loadTexture(size_t location, std::string texture_name) {
    Texture *texture = load_texture_png(resource_location+texture_location+texture_name);
    if(texture != nullptr) texture_map[location] = std::unique_ptr<Texture>(texture);

    GLTexture *gl_texture = TextureGLHandler::createTexture(texture);
    if(gl_texture != nullptr) gl_texture_map[location] = std::unique_ptr<GLTexture>(gl_texture);
}

void TextureManager::loadAtlas(size_t location, std::set<size_t> locations) {
    TextureAtlas* texture_atlas = TextureAtlasGenerator::generateTextureAtlas(texture_map, 512, 512, locations);
    if(texture_atlas != nullptr) atlas_map[location] = std::unique_ptr<TextureAtlas>(texture_atlas);

    GLTexture *gl_texture = TextureGLHandler::createTexture(texture_atlas->getTexture());
    if(gl_texture != nullptr) gl_texture_map[location] = std::unique_ptr<GLTexture>(gl_texture);
}