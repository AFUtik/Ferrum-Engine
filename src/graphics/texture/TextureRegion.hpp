#ifndef TEXTUREATLASPOS_HPP
#define TEXTUREATLASPOS_HPP

struct TextureRegion {
    float u1, u2;
    float v1, v2;
    /* Variables that store uv coords with no padding. */
    float orig_u1, orig_u2;
    float orig_v1, orig_v2;
};

#endif