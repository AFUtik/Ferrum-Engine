#include "ResourceManager.hpp"

ResourceManager::ResourceManager() : 
texture_m(new TextureManager(location)) {
    model_m = std::make_unique<ModelManager>(texture_m.get());
}

std::string ResourceManager::getLocation() const {
    return location;
}

void ResourceManager::changeResourceLocation(std::string resource_location) {
    location = resource_location;
}

ModelManager* ResourceManager::getModelManager() {
    return model_m.get();
}

TextureManager* ResourceManager::getTextureManager() {
    return texture_m.get();
}
