#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <memory>
#include <unordered_map>
#include <set>
#include <string>

#include "TextureAtlas.hpp"
#include "Texture.hpp"
#include "GLTexture.hpp"

typedef std::unordered_map<size_t, std::unique_ptr<TextureAtlas>> AtlasMap;
typedef std::unordered_map<size_t, std::unique_ptr<Texture>> TextureMap;
typedef std::unordered_map<size_t, std::unique_ptr<GLTexture>> GLTextureMap;

class TextureManager {
private:
    GLTextureMap gl_texture_map;
    TextureMap texture_map;
    AtlasMap atlas_map;
    
    std::string resource_location;
    std::string texture_location;
public:
    TextureManager(std::string resource_location);
    void changeTextureLocation(std::string texture_location);

    //const AtlasMap& getAtlasMap();
    const TextureMap& getTextureMap();
    const GLTextureMap& getGLTextureMap();

    GLTexture* getGLTexture(size_t location);
    TextureAtlas* getAtlas(size_t location);
    Texture* getTexture(size_t location);
    
    void loadTexture(size_t location, std::string texture_name);
    void loadAtlas(size_t location, std::set<size_t> locations);
};

#endif