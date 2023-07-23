#ifndef CAMERA_H
#define CAMERA_H

#include "vect.h"


typedef struct camera {
    ANG3D ang;
    VEC3D pos;
    VEC3D drwpln;
    int active;
} CAMERA;

void update_camera_pos (CAMERA* camera, VEC3D new_pos);
void update_camera_ang (CAMERA* camera, ANG3D new_ang);

CAMERA create_camera (ANG3D ang, VEC3D pos, VEC3D ddist);

#endif