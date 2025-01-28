#ifndef TEXTUREHANDLER_HPP
#define TEXTUREHANDLER_HPP

class GLTexture;
class Texture;

class TextureGLHandler {
public:
    static GLTexture* createTexture(Texture* texture);
};

#endif