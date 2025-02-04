#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <memory>
#include <unordered_map>
#include <map>
#include <set>
#include <string>

#include "TextureAtlas.hpp"
#include "Texture.hpp"

typedef std::unordered_map<std::string, std::map<size_t, Texture*>> TextureGroup;
typedef std::unordered_map<size_t, std::unique_ptr<Texture>> TextureMap;
typedef std::unordered_map<size_t, std::unique_ptr<TextureAtlas>> AtlasMap;

class TextureManager {
private:
    TextureGroup texture_group;
    TextureMap texture_m;
    AtlasMap atlas_m;

    bool cleared = false;
    
    std::string resource_location;
    std::string texture_location;
public:
    TextureManager(std::string resource_location);
    void changeTextureLocation(std::string texture_location);

    void loadTextureToGroup(std::string group_tag, size_t tex_loc, Texture* texture);
    const std::map<size_t, std::unique_ptr<Texture>>& getTexturesByGroup(std::string group_tag);
    
    void loadTexture(size_t tex_loc, Texture* texture);
    Texture* getTexture(size_t location);
    const TextureMap& getTextureMap();

    void loadAtlasByGroups(size_t atlas_loc, std::set<std::string> group_tags);
    void loadAtlasByTex(size_t atlas_loc, std::set<size_t> tex_locs);
    TextureAtlas* getAtlas(size_t location);

    void clearTextures();
};

#endif