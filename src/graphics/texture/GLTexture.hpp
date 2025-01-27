#ifndef GLTEXTURE_HPP
#define GLTEXTURE_HPP

class GLTexture {
private:
    unsigned int texture_id;
public:
    GLTexture();
    ~GLTexture();

    void bind();
};

#endif