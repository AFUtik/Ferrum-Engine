#ifndef TEXTUREHANDLER_HPP
#define TEXTUREHANDLER_HPP

#include <string>

class Texture;

extern Texture* load_texture_png(std::string filename);
extern bool save_texture_png(std::string filename, Texture* texture);

#endif // !TEXTURE_LOADER_HPP
