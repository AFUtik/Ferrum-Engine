#ifndef GUILLOTINE_HPP
#define GUILLOTINE_HPP

#include "../structures/Rectangle.hpp"
#include <vector>

// The algorithm below is designed to pack textures into a Texture Atlas. //

class GuillotinePacker {
private:
    int atlasWidth, atlasHeight;
    std::vector<Rectangle> freeRectangles;
    
    void splitRectangle(const Rectangle& freeRect, const Rectangle& usedRect);
public:
    GuillotinePacker(int initialWidth, int initialHeight)
        : atlasWidth(initialWidth), atlasHeight(initialHeight) {
        freeRectangles.push_back(Rectangle(0, 0, atlasWidth, atlasHeight));
    }

    bool pack(Rectangle& tile);

    inline int getAtlasWidth() const { return atlasWidth; }
    inline int getAtlasHeight() const { return atlasHeight; }
};

#endif