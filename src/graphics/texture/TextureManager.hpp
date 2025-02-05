#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <memory>
#include <unordered_map>
#include <string>

#include "TextureAtlas.hpp"
#include "Texture.hpp"

typedef std::unordered_map<size_t, std::unique_ptr<Texture>> TextureMap;
typedef std::unordered_map<size_t, std::unique_ptr<TextureAtlas>> AtlasMap;

class TextureGroup {
protected:
    std::unordered_map<std::string, TextureGroup> subgroups;
    std::vector<size_t> *parent_locations;
    std::vector<size_t> locations;

    friend class TextureManager;
public:
    TextureGroup() : parent_locations(nullptr) {}

    void loadLocation(const size_t &location) const;

    const std::vector<size_t>& getLocations() const;

    const TextureGroup& findGroup(const std::string tag);
};

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

    void loadBunchToGroup(std::string group_tag, size_t tex_loc, const std::vector<std::string> &paths);
    void loadTextureToGroup(std::string group_tag, size_t tex_loc, std::string path);

    void loadTexture(size_t tex_loc, const std::string &path);

    void loadAtlasByGroups(size_t atlas_loc, std::vector<std::string> group_tags);
    void loadAtlasByTex(size_t atlas_loc, std::vector<size_t> tex_locs);


    const std::vector<size_t>& getTexturesByGroup(std::string group_tag);
    TextureAtlas* getAtlas(size_t location);
    Texture* getTexture(size_t location);
    const TextureMap& getTextureMap();

    void clearTextures();
};


#endif