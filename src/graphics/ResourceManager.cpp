#include "ResourceManager.hpp"

std::string ResourceManager::location;

ResourceManager::ResourceManager() : texture_m(new TextureManager(location)) {
    model_m = std::make_unique<ModelManager>(texture_m.get());
}

std::string ResourceManager::getLocation() const {
    return location;
}

ModelManager* ResourceManager::getModelManager() {
    return model_m.get();
}

TextureManager* ResourceManager::getTextureManager() {
    return texture_m.get();
}

void ResourceManager::setLocation(std::string resource_location) {
    location = resource_location;
}