#ifndef IMPORT_FILE_H
#define IMPORT_FILE_H

#include "vect.h"

int size_of_file (unsigned char* raw_file);

VEC3D* mod_import_vects(char* filename);
EDGE* mod_import_edges(char* filename);
TRIANG* mod_import_tris(char* filename);

MODEL mod_import (char* filename);

#endif