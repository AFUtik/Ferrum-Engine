#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

struct Rectangle {
    float x, y;
    float x2, y2;
    float width, height;

    Rectangle(int x = 0, int y = 0, int width = 0, int height = 0)
        : x(x), y(y), x2(x+width), y2(y+height), width(width), height(height){}

    inline bool canFit(int tileWidth, int tileHeight) const {
        return width >= tileWidth && height >= tileHeight;
    }

    inline bool intersect(float nx, float ny) const {
        return (x2 > nx && nx > x) && (y2 > ny && ny > y);
    }
};

#endif