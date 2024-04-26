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
    //rotate_mod (init_model, init_model->rot);

    norm_ang_quat (&(init_model->rot));
    float x_bar = 0;
    float y_bar = 0;
    float z_bar = 0;

    for(int l=1; l<((int)init_model->vecs[0].i + 1);l++) {
        if (!((init_model->rot.x == 0 && init_model->rot.y == 0 && init_model->rot.z == 0) || init_model->rot.w == 0)){
            float temp_x = init_model->vecs[l].i - x_bar;
            float temp_y = init_model->vecs[l].j - y_bar;
            float temp_z = init_model->vecs[l].k - z_bar;


            init_model->rot_vecs[l].i = (temp_x*(1-2*pow(init_model->rot.y,2)-2*pow(init_model->rot.z,2))) + (temp_y*((2*init_model->rot.x*init_model->rot.y)-(2*init_model->rot.w*init_model->rot.z))) + (temp_z*((2*init_model->rot.x*init_model->rot.z)+(init_model->rot.w*init_model->rot.y))) + x_bar;
            init_model->rot_vecs[l].j = (temp_x*((2*init_model->rot.x*init_model->rot.y)+(2*init_model->rot.w*init_model->rot.z))) + (temp_y*(1-2*pow(init_model->rot.x,2)-2*pow(init_model->rot.z,2))) + (temp_z*((2*init_model->rot.y*init_model->rot.z)-(init_model->rot.w*init_model->rot.x))) + y_bar;
            init_model->rot_vecs[l].k = (temp_x*((2*init_model->rot.x*init_model->rot.z)-(init_model->rot.w*init_model->rot.y))) + (temp_y*((2*init_model->rot.y*init_model->rot.z)+(init_model->rot.w*init_model->rot.x))) + (temp_z*(1-2*pow(init_model->rot.x,2)-2*pow(init_model->rot.y,2))) + z_bar;
            init_model->rot_vecs[l].w = 1;
            

            VEC3D temp = {(init_model->rot_vecs[l].i*init_model->scale) + init_model->pos.i, (init_model->rot_vecs[l].j*init_model->scale) + init_model->pos.j, (init_model->rot_vecs[l].k*init_model->scale) + init_model->pos.k};
            init_model->tvecs[l] = point_3t2(temp, camera);
            // printf ("(%f, %f, %f)\n", init_model->pos.i, init_model->pos.j, init_model->pos.k);
            // printf ("(%f, %f, %f) -> (%f, %f)\n", temp.i, temp.j, temp.k, init_model->tvecs[l].i, init_model->tvecs[l].j);
        } else {
            init_model->rot_vecs[l].i = init_model->vecs[l].i;
            init_model->rot_vecs[l].j = init_model->vecs[l].j;
            init_model->rot_vecs[l].k = init_model->vecs[l].k;
            init_model->rot_vecs[l].w = 1;

            VEC3D temp = {(init_model->rot_vecs[l].i*init_model->scale) + init_model->pos.i, (init_model->rot_vecs[l].j*init_model->scale) + init_model->pos.j, (init_model->rot_vecs[l].k*init_model->scale) + init_model->pos.k};
            init_model->tvecs[l] = point_3t2 (temp, camera);
        }
    }
}