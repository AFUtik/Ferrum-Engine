#ifndef RENDERER_HPP
#define RENDERER_HPP

class TextureManager;
class ModelManager;

class Renderer {
public:
    TextureManager* texture_m;
    ModelManager* model_m;
};

#endif