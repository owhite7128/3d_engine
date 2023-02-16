#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "vect.h"
#include "model.h"
#include "camera.h"

VEC2D point_3t2 (VEC3D vec, CAMERA camera);

void model_tfrm (MODEL init_model, CAMERA camera);

void rotate_mod (MODEL init_model, ANG3D rot);

#endif