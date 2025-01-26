#ifndef TEXTUREATLAS_HPP
#define TEXTUREATLAS_HPP

#include <vector>

class Texture;

class TextureAtlas {
private:
    unsigned int texture_id;
    Texture* texture;
    //size_t index;
public:
    TextureAtlas(int size);
    ~TextureAtlas();

    void addTexture(Texture* texture);

    void init();
};

#endif