#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "vect.h"
#include "model.h"
#include "camera.h"


#define OOB 3.4E+38

VEC2D point_3t2 (VEC3D vec, CAMERA camera);

void model_tfrm (MODEL *init_model, CAMERA camera);

#endif