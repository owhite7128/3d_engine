#ifndef IMPORT_OBJ_H
#define IMPORT_OBJ_H

#include "vect.h"
#include "model.h"

MODEL import_model (char* filename);

VEC3D* create_vecs (char* file_buffer, int sz);

FACE* create_faces (char* file_buffer, int sz);

#endif