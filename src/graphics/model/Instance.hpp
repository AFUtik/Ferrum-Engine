#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#define INSTANCE_WORLD_POS_OFFSET 0
#define INSTANCE_TEXTURE_POS_OFFSET 16
#define INSTANCE_DATA_LENGTH (16+2) // MATRIX4X4 + VEC2 //

struct Instance {
    float data[INSTANCE_DATA_LENGTH] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f
    };
};

#endif