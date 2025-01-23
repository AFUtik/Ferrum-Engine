#ifndef RENDERER_HPP
#define RENDERER_HPP

class DrawContext;
class Drawable;
class Mesh;
class Texture;

#include <forward_list>
#include <vector>

#define VERTEX_SIZE (3+2)

static int attrs[] = { 3,2,0, 0 };

class Renderer {
public:
    std::vector<Texture*> textures;
    std::vector<Mesh*> meshes;
    std::forward_list<Drawable*> objects;

    virtual void draw(DrawContext* draw_context) = 0;
};

#endif