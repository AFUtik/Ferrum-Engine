#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <memory>
#include <unordered_map>
#include <string>

#include "Tilemap.hpp"
#include "Texture.hpp"

#include "../../utils/structures/TagGroup.hpp"

class TextureManager {
private:
    TagGroup<std::string> texture_group;

    std::unordered_map<std::string, std::unique_ptr<Texture>> texture_m;
    std::unordered_map<std::string, std::unique_ptr<Tilemap>> tilemap_m;
    
    std::string resource_location;
    std::string texture_location;
public:
    TextureManager(std::string resource_location);
    void changeTextureLocation(std::string texture_location);

    void loadBunchToGroup(std::string group_tag, std::string tex_loc, const std::vector<std::string> &paths);
    void loadTextureToGroup(std::string group_tag, std::string tex_loc, std::string path);

    void loadTexture(std::string tex_loc, const std::string &path);
    
    void loadTilemapByGroup(std::string tilemap_loc, std::string group_tag);
    void loadTilemapByTex(std::string tilemap_loc, const std::vector<std::string> &tex_locs);

    const std::vector<std::string>& getTexturesByGroup(std::string group_tag);

    Tilemap* getTilemap(std::string location);
    Texture* getTexture(std::string location);

    void clearTextures();
};


#endif