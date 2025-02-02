#ifndef GUILLOTINE_HPP
#define GUILLOTINE_HPP

#include <vector>

// The algorithm below is designed to pack textures into a Texture Atlas.
struct Rectangle {
    unsigned int x, y;
    unsigned int width, height;
    size_t data;

    Rectangle(int x = 0, int y = 0, int width = 0, int height = 0)
        : x(x), y(y), width(width), height(height){}

    inline bool canFit(int tileWidth, int tileHeight) const {
        return width >= tileWidth && height >= tileHeight;
    }
};

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