#ifndef VECT_H
#define VECT_H

typedef struct ang3d {
    float x;
    float y;
    float z;
    float w;
} ANG3D;

typedef struct vec3d {
    float i;
    float j;
    float k;
    float w;
} VEC3D;

typedef struct vec2d {
    float i;
    float j;
    int k;
} VEC2D;

// VEC3D ZERO_VECTOR_3D = {0, 0, 0, 0};

void norm_ang_quat(ANG3D* rot);

VEC3D vec_cross (VEC3D vecA, VEC3D vecB);

float vec3_len (VEC3D vecA, VEC3D vecB);

VEC3D vec3_sub (VEC3D v1, VEC3D v2);

VEC3D vec3_norm (VEC3D vec, float len);

float vec3_dot (VEC3D vecA, VEC3D vecB);

float vec2_dot (VEC2D vecA, VEC2D vecB);

#endif