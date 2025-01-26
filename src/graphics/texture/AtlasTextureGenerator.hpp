#ifndef ATLASTEXTUREGENERATOR_HPP
#define ATLASTEXTUREGENERATOR_HPP

class TextureManager;

class AtlasTextureGenerator {
private:
    TextureManager* texture_manager;
public:
    void generate_atlas();
};

#endif