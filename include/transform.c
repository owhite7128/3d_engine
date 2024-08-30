#include "transform.h"
#include "vect.h"
#include "model.h"
#include "camera.h"
#include "rotate.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

VEC2D point_3t2 (VEC3D vec, CAMERA camera) {
    VEC2D p_vec;
    p_vec.k = 1;
    VEC3D rot_vec;
    rot_vec.w = 1;

    if (vec.k > camera.pos.k) {
        p_vec.i = OOB;
        p_vec.j = OOB;
        return p_vec;
    }

    rot_vec.i = cos(camera.ang.y) * (sin(camera.ang.z) * (vec.j - camera.pos.j) + cos(camera.ang.z) * (vec.i - camera.pos.i)) - sin(camera.ang.y) * (vec.k - camera.pos.k);
    rot_vec.j = sin(camera.ang.x) * (cos(camera.ang.y) * (vec.k - camera.pos.k)) + sin(camera.ang.y) * (sin(camera.ang.z) * (vec.j - camera.pos.j) + cos(camera.ang.z) * (vec.i - camera.pos.i)) + cos(camera.ang.x) * (cos(camera.ang.z) * (vec.j - camera.pos.j) - sin(camera.ang.z) * (vec.i - camera.pos.i));
    rot_vec.k = cos(camera.ang.x) * (cos(camera.ang.y) * (vec.k - camera.pos.k)) + sin(camera.ang.y) * (sin(camera.ang.z) * (vec.j - camera.pos.j) + cos(camera.ang.z) * (vec.i - camera.pos.i)) - sin(camera.ang.x) * (cos(camera.ang.z) * (vec.j - camera.pos.j) - sin(camera.ang.z) * (vec.i - camera.pos.i));

    p_vec.i = ((camera.drwpln.k * rot_vec.i) / (rot_vec.k)) + camera.drwpln.i;
    p_vec.j = ((camera.drwpln.k * rot_vec.j) / (rot_vec.k)) + camera.drwpln.j;

    //printf ("Camera: pos:(%f, %f, %f) ang:(%f, %f, %f) dpln:(%f, %f, %f)\n", camera.pos.i, camera.pos.j, camera.pos.k, camera.ang.x, camera.ang.y, camera.ang.z, camera.drwpln.i, camera.drwpln.j, camera.drwpln.k);
    //printf ("TFRM: (%f, %f, %f) + (%f, %f, %f) -> (%f, %f)\n", vec.i, vec.j, vec.k, rot_vec.i, rot_vec.j, rot_vec.k, p_vec.i, p_vec.j);

    return p_vec;
}

void model_tfrm (MODEL *init_model, CAMERA camera) {
    rotate_mod (init_model, init_model->rot);

    for(int l=1; l<((int)init_model->vecs[0].i + 1);l++) {
        VEC3D temp = {(init_model->rot_vecs[l].i*init_model->scale) + init_model->pos.i, (init_model->rot_vecs[l].j*init_model->scale) + init_model->pos.j, (init_model->rot_vecs[l].k*init_model->scale) + init_model->pos.k};
        init_model->tvecs[l] = point_3t2 (temp, camera);
    }
}