#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <memory>
#include <map>
#include <string>

#include "Texture.hpp"

class TextureManager {
private:
    std::map<size_t, std::unique_ptr<Texture>> texture_map;
    std::string *resource_location;
    std::string texture_location;
public:
    TextureManager(std::string &resource_location);
    // virtual ~TextureManager();

    Texture* getTexture(size_t location);
    void loadTexture(size_t location, std::string texture_name);

    void changeTextureLocation(std::string texture_location);
};

#endif