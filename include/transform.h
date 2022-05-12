#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "vect.h"
#include "model.h"

VEC2D point_3t2 (VEC3D vec, ANG3D ang, VEC3D cpos, VEC3D ddist);

void model_tfrm (MODEL init_model, ANG3D ang, VEC3D cpos, VEC3D ddist);

void rotate_mod (MODEL init_model, ANG3D rot);

#endif