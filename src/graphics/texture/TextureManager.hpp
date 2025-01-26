#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <memory>
#include <map>
#include <string>

#include "Texture.hpp"

typedef std::map<size_t, std::map<size_t, std::unique_ptr<Texture>>> TextureMap;

class TextureManager {
private:
    TextureMap texture_map;
    std::string *resource_location;
    std::string texture_location;
public:
    TextureManager(std::string &resource_location);
    void changeTextureLocation(std::string texture_location);

    const TextureMap& getTextureMap();

    Texture* getTexture(size_t location);
    void loadTexture(size_t category, size_t location, std::string texture_name);

};

#endif