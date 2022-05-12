#ifndef MODEL_H
#define MODEL_H

#include "vect.h"

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