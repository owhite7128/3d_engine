#ifndef MODEL_H
#define MODEL_H

#include "vect.h"

typedef struct triang {
    int s;
    int m;
    int e;
} TRIANG;

typedef struct face {
    int one;
    int two;
    int three;
    int four;
    int draw;
} FACE;

typedef struct edge {
    int s;
    int e;
} EDGE;

typedef struct model {
    VEC3D* vecs;
    VEC2D* tvecs;
    EDGE* edgs;
    TRIANG* tris;
    FACE* faces;
    int id;
} MODEL;

void destroy_model (MODEL model);

#endif