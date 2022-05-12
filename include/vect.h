#ifndef VECT_H
#define VECT_H

typedef struct vec3d {
    float i;
    float j;
    float k;
    int w;
} VEC3D;

typedef struct vec2d {
    float i;
    float j;
    int k;
} VEC2D;

VEC3D vec_cross (VEC3D vecA, VEC3D vecB);

float vec3_dot (VEC3D vecA, VEC3D vecB);

float vec2_dot (VEC2D vecA, VEC2D vecB);

#endif