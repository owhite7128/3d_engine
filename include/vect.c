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
    crossProd.i = (vecA.j * vecB.k) - (vecA.k * vecB.j);
    crossProd.j = (vecA.k * vecB.i) - (vecA.i * vecB.k);
    crossProd.k = (vecA.i * vecB.j) - (vecA.j * vecB.i);

    return crossProd;
}

float vec3_len (VEC3D vecA, VEC3D vecB)
{
    return sqrt (pow(vecA.i - vecB.i, 2) + pow(vecA.j - vecB.j, 2) + pow(vecA.k - vecB.k, 2));
}

VEC3D vec3_norm (VEC3D vec, float len)
{
    VEC3D ret;
    ret.i = vec.i / len;
    ret.j = vec.j / len;
    ret.k = vec.k / len;
    ret.w = vec.w;

    return ret;
}

VEC3D vec3_sub (VEC3D v1, VEC3D v2)
{
    VEC3D ret;
    ret.i = v1.i - v2.i;
    ret.j = v1.j - v2.j;
    ret.k = v1.k - v2.k;
    ret.w = v1.w;

    return ret;
}

float vec3_dot (VEC3D vecA, VEC3D vecB) {
    float dot = vecA.i * vecB.i + vecA.j * vecB.j + vecA.k * vecB.k;

    return dot;
}

float vec2_dot (VEC2D vecA, VEC2D vecB) {
    float dot = vecA.i * vecB.i + vecA.j*vecB.j;

    return dot;
}