#ifndef DRAWCONTEXT_HPP
#define DRAWCONTEXT_HPP

#include <string>
#include <vector>
#include <memory>

class Camera;
class Texture;
class Mesh;
class Drawable;

class EntityRenderer;
class ChunkRenderer;

class DrawContext {
public:
    EntityRenderer *entity_renderer;
    ChunkRenderer *chunk_renderer;

    DrawContext();
    ~DrawContext();

    Camera *camera;
    //std::vector<Light*> lights //
    std::string frag_shader;
    std::string vertex_shader;

    void draw_all();
};

#endif