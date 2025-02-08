#include "MatrixUtils.hpp"


void Matrix4x4ArrayUtils::fill(float *array, float value) {
    for(int i = 0; i < 16; i++) array[i] = 0.0f;
    array[0] = value;
    array[5] = value;
    array[10] = value;
    array[15] = value;
}

void Matrix4x4ArrayUtils::setPosition(float *array, const glm::vec3 &glm_pos) {
    array[12] = glm_pos.x;
    array[13] = glm_pos.y;
    array[14] = glm_pos.z;
}