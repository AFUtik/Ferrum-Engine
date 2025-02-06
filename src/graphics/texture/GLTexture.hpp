#ifndef GLTEXTURE_HPP
#define GLTEXTURE_HPP

class GLTexture {
public:
    unsigned int texture_id;

    GLTexture() {};
    ~GLTexture();

    void bind();
};

#endif