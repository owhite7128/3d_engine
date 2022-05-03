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

typedef struct ang3d {
    float x;
    float y;
    float z;
} ANG3D;

typedef struct triang {
    int s;
    int m;
    int e;
} TRIANG;

typedef struct edge {
    int s;
    int e;
} EDGE;

typedef struct model {
    VEC3D* vecs;
    VEC2D* tvecs;
    EDGE* edgs;
    TRIANG* tris;
    int id;
} MODEL;

#endif