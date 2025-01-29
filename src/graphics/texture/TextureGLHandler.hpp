#ifndef TEXTUREGLHANDLER_HPP
#define TEXTUREGLHANDLER_HPP

class GLTexture;
class Texture;

class TextureGLHandler {
public:
    static GLTexture* createTexture(Texture* texture);
};

#endif