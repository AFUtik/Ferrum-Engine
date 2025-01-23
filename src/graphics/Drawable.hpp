#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "glm/glm.hpp"

class Drawable {
public:
    bool relevant;
    int &x;
    int &y;
    int &z;

    Drawable(int &x, int &y, int &z) : x(x), y(y), z(z), relevant(true) {}; 
};

#endif