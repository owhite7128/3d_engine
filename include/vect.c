#include "vect.h"
#include <math.h>

void norm_ang_quat(ANG3D* rot) {
    float length = sqrt(pow(rot->x,2)+pow(rot->y,2)+pow(rot->z,2));

    rot->x /= length;
    rot->y /= length;
    rot->z /= length;

    rot->x *= sin(rot->w / 2);
    rot->y *= sin(rot->w / 2);
    rot->z *= sin(rot->w / 2);
    
    rot->w = cos(rot->w / 2);
    return;
}

VEC3D vec_cross (VEC3D vecA, VEC3D vecB) {
    VEC3D crossProd;
    crossProd.w = 1;
    crossProd.i = vecA.j * vecB.k - vecA.k * vecB.j;
    crossProd.j = vecA.k * vecB.i - vecA.i * vecB.k;
    crossProd.k = vecA.i * vecB.j - vecA.j * vecB.i;

    return crossProd;
}

float vec3_dot (VEC3D vecA, VEC3D vecB) {
    float dot = vecA.i * vecB.i + vecA.j * vecB.j + vecA.k * vecB.k;

    return dot;
}

float vec2_dot (VEC2D vecA, VEC2D vecB) {
    float dot = vecA.i * vecB.i + vecA.j + vecB.j;

    return dot;
}