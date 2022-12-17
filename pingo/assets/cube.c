#include "cube.h"

Vec3f ver[36] = {
    {-0.5, +0.5, -0.5},{+0.5, -0.5, -0.5},{-0.5, -0.5, -0.5},
    {-0.5, +0.5, -0.5},{+0.5, +0.5, -0.5},{+0.5, -0.5, -0.5},
    {-0.5, -0.5, +0.5},{+0.5, -0.5, +0.5},{-0.5, +0.5, +0.5},
    {-0.5, +0.5, +0.5},{+0.5, -0.5, +0.5},{+0.5, +0.5, +0.5},

    {+0.5, -0.5, -0.5},{-0.5, -0.5, +0.5},{-0.5, -0.5, -0.5},
    {+0.5, -0.5, -0.5},{+0.5, -0.5, +0.5},{-0.5, -0.5, +0.5},
    {+0.5, +0.5, -0.5},{-0.5, +0.5, -0.5},{-0.5, +0.5, +0.5},
    {-0.5, +0.5, +0.5},{+0.5, +0.5, +0.5},{+0.5, +0.5, -0.5},

    {-0.5, +0.5, -0.5},{-0.5, -0.5, -0.5},{-0.5, -0.5, +0.5},
    {-0.5, -0.5, +0.5},{-0.5, +0.5, +0.5},{-0.5, +0.5, -0.5},
    {+0.5, -0.5, -0.5},{+0.5, +0.5, -0.5},{+0.5, -0.5, +0.5},
    {+0.5, +0.5, +0.5},{+0.5, -0.5, +0.5},{+0.5, +0.5, -0.5}
};

Vec2f tex[36] = {
     {0.0, 1.0},{1.0, 0.0},{0.0, 0.0},
     {0.0, 1.0},{1.0, 1.0},{1.0, 0.0},
     {1.0, 1.0},{1.0, 0.0},{0.0, 1.0},
     {1.0, 0.0},{0.0, 1.0},{1.0, 1.0},

     {1.0, 0.0},{0.0, 1.0},{0.0, 0.0},
     {1.0, 0.0},{1.0, 1.0},{0.0, 1.0},
     {1.0, 0.0},{0.0, 0.0},{0.0, 1.0},
     {0.0, 1.0},{1.0, 1.0},{1.0, 0.0},

     {1.0, 0.0},{0.0, 0.0},{0.0, 1.0},
     {0.0, 1.0},{1.0, 1.0},{1.0, 0.0},
     {0.0, 0.0},{1.0, 0.0},{0.0, 1.0},
     {1.0, 1.0},{0.0, 1.0},{1.0, 0.0}

};

uint16_t i[36] = {
    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,
    17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35
};


Mesh mesh_cube = {
    .indexes_count = 36,
    .pos_indices = &i[0],
    .positions = &ver[0],
    .textCoord = &tex[0],
    .tex_indices = &i[0]
};
