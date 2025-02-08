#ifndef MATRIXUTILS_HPP
#define MATRIXUTILS_HPP

#include "glm/glm.hpp"

class Matrix4x4ArrayUtils {
public:
    static void fill(float *array, float value);

    static void setPosition(float *array, const glm::vec3 &glm_pos);
    //static void setPosition(float *array, float *arr_pos);

    //static void setRotation();
    //static void setScale();
};

#endif