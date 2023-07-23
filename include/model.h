#ifndef MODEL_H
#define MODEL_H

#include "vect.h"

typedef struct triang {
    int s;
    int m;
    int e;
    int draw;
    int color;
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
    VEC3D pos;
    int id;
    float scale;
} MODEL;

typedef struct model_list_node {
    MODEL* curr;
    struct model_list_node* next;
} MODEL_NODE;

typedef struct model_list {
    MODEL_NODE* head;
    MODEL_NODE* tail;
    int length;
} MODEL_LIST;

void destroy_model (MODEL* model);

void add_model (MODEL_LIST* mod_list, char* file_name, VEC3D in_pos, ANG3D in_rot, float in_scale);

void move_model (MODEL* mod, VEC3D pos);

void set_model (MODEL* mod, VEC3D pos);

MODEL_LIST* create_model_list ();

MODEL_NODE* new_model_node (MODEL* mod);

void destory_model_list ();

#endif