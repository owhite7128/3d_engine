#ifndef IMPORT_OBJ_H
#define IMPORT_OBJ_H

#include "vect.h"
#include "model.h"

#define MODEL_IMPORT_OBJ 0

MODEL* import_model (char* filename, int model_type);

VEC3D* create_vecs (char* file_buffer, int sz);

FACE* create_faces (char* file_buffer, int sz);

TRIANG* create_tris (char* file_buffer, int sz);

#endif