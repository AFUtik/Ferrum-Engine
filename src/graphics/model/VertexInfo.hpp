#pragma once

#define COORD_SIZE 3
#define TEX_COORD_SIZE 2
#define VERTEX_SIZE (COORD_SIZE+TEX_COORD_SIZE)

#define TRIANGLE_INDEX_SIZE 3
#define QUAD_INDEX_SIZE 6
#define CUBE_INDEX_SIZE 36

#define QUAD_VERTEX_SIZE 4

static unsigned int attrs[] = {COORD_SIZE, TEX_COORD_SIZE, 0};
