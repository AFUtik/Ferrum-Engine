#ifndef RENDERER_HPP
#define RENDERER_HPP

class DrawContext;
class Drawable;
class Mesh;
class Texture;

#include <vector>

#define VERTEX_SIZE (3+2)

static int attrs[] = { 3,2,0, 0 };

class Renderer {
public:
    std::vector<Texture*> textures;
    std::vector<Mesh*> meshes;
};

#endif