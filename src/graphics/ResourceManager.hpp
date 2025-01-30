#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <string>
#include <memory>

#include "model/ModelManager.hpp"
#include "texture/TextureManager.hpp"

class ResourceManager { 
private:
    //std::unique_ptr<Shader> shader_m;
    std::unique_ptr<ModelManager> model_m;
    std::unique_ptr<TextureManager> texture_m;

    std::string location;
public:
    ResourceManager(std::string location);

    std::string getLocation() const;
    void changeResourceLocation(std::string resource_location);

    ModelManager* getModelManager();
    TextureManager* getTextureManager();
};

#endif