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
    TextureAtlas(Texture* texture) : texture(texture) {};
    ~TextureAtlas();

    Texture* getTexture();
    void addTexture(Texture* texture);

    void init();
};

#endif