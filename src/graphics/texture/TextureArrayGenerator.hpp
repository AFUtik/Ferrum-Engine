#ifndef TEXTUREARRAYGENERATOR_HPP
#define TEXTUREARRAYGENERATOR_HPP

class TextureManager;

class TextureArrayGenerator {
private:
    TextureManager* texture_manager;
public:
    TextureArrayGenerator(TextureManager* texture_manager);

    void generateTextureArray(unsigned int start, unsigned int end);
};

#endif