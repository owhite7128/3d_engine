#include "camera.h"
#include <stdlib.h>


void update_camera_pos (CAMERA *camera, VEC3D new_pos)
{
    camera->pos.i = new_pos.i;
    camera->pos.j = -new_pos.j;
    camera->pos.k = new_pos.k;
    camera->pos.w = new_pos.w;
}

void update_camera_ang (CAMERA *camera, ANG3D new_ang)
{
    camera->ang.x = new_ang.x;
    camera->ang.y = new_ang.y;
    camera->ang.z = new_ang.z;
    camera->ang.w = new_ang.w;
}

CAMERA* create_camera (ANG3D ang, VEC3D pos, VEC3D ddist) {
    CAMERA *camera;
    camera = (CAMERA*) malloc (1*sizeof(CAMERA));
    
    update_camera_ang (camera, ang);
    update_camera_pos (camera, pos);
    camera->drwpln.i = ddist.i;
    camera->drwpln.j = ddist.j;
    camera->drwpln.k = ddist.k;
    camera->drwpln.w = ddist.w;

    camera->active = 1;
    return camera;
}

void destory_camera (CAMERA *camera) {
    free (camera);
}