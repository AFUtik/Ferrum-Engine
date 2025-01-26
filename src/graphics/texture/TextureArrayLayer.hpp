#ifndef TEXTUREARRAYLAYER_HPP
#define TEXTUREARRAYLAYER_HPP

#include <memory>
#include <map>
#include <string>

#include "Texture.hpp"

class TextureArrayLayer {
private:
    
    size_t layer;
public:
    size_t getLayer();
};

#endif