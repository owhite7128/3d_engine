#include "transform.h"
#include "vect.h"
#include "model.h"
#include "camera.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

VEC2D point_3t2 (VEC3D vec, CAMERA camera) {
    VEC2D p_vec;
    p_vec.k = 1;
    VEC3D rot_vec;
    rot_vec.w = 1;
    
    rot_vec.i = cos(camera.ang.y) * (sin(camera.ang.z) * (vec.j - camera.pos.j) + cos(camera.ang.z) * (vec.i - camera.pos.i)) - sin(camera.ang.y) * (vec.k - camera.pos.k);
    rot_vec.j = sin(camera.ang.x) * (cos(camera.ang.y) * (vec.k - camera.pos.k)) + sin(camera.ang.y) * (sin(camera.ang.z) * (vec.j - camera.pos.j) + cos(camera.ang.z) * (vec.i - camera.pos.i)) + cos(camera.ang.x) * (cos(camera.ang.z) * (vec.j - camera.pos.j) - sin(camera.ang.z) * (vec.i - camera.pos.i));
    rot_vec.k = cos(camera.ang.x) * (cos(camera.ang.y) * (vec.k - camera.pos.k)) + sin(camera.ang.y) * (sin(camera.ang.z) * (vec.j - camera.pos.j) + cos(camera.ang.z) * (vec.i - camera.pos.i)) - sin(camera.ang.x) * (cos(camera.ang.z) * (vec.j - camera.pos.j) - sin(camera.ang.z) * (vec.i - camera.pos.i));

    p_vec.i = ((camera.drwpln.k * rot_vec.i) / (rot_vec.k)) + camera.drwpln.i;
    p_vec.j = ((camera.drwpln.k * rot_vec.j) / (rot_vec.k)) + camera.drwpln.j;

    return p_vec;
}

void model_tfrm (MODEL init_model, CAMERA camera) {
    for(int l=1; l<((int)init_model.vecs[0].i + 1);l++) {
        init_model.tvecs[l] = point_3t2(init_model.vecs[l], camera);
    }
}


//ROTATION DOESN'T REALLY WORK
void rotate_mod(MODEL init_model, ANG3D rot) {
    norm_ang_quat (&rot);
    float x_bar = 0;
    float y_bar = 0;
    float z_bar = 0;

    for(int l=1; l<((int)init_model.vecs[0].i + 1); l++) {
        x_bar += init_model.vecs[l].i;
        y_bar += init_model.vecs[l].j;
        z_bar += init_model.vecs[l].k;
    }

    x_bar /= init_model.vecs[0].i;
    y_bar /= init_model.vecs[0].i;
    z_bar /= init_model.vecs[0].i;


    for (int l=1; l<((int)init_model.vecs[0].i + 1); l++) {
        float temp_x = init_model.vecs[l].i - x_bar;
        float temp_y = init_model.vecs[l].j - y_bar;
        float temp_z = init_model.vecs[l].k - z_bar;


        init_model.vecs[l].i = (temp_x*(1-2*pow(rot.y,2)-2*pow(rot.z,2))) + (temp_y*((2*rot.x*rot.y)-(2*rot.w*rot.z))) + (temp_z*((2*rot.x*rot.z)+(rot.w*rot.y))) + x_bar;
        init_model.vecs[l].j = (temp_x*((2*rot.x*rot.y)+(2*rot.w*rot.z))) + (temp_y*(1-2*pow(rot.x,2)-2*pow(rot.z,2))) + (temp_z*((2*rot.y*rot.z)-(rot.w*rot.x))) + y_bar;
        init_model.vecs[l].k = (temp_x*((2*rot.x*rot.z)-(rot.w*rot.y))) + (temp_y*((2*rot.y*rot.z)+(rot.w*rot.x))) + (temp_z*(1-2*pow(rot.x,2)-2*pow(rot.y,2))) + z_bar;
        init_model.vecs[l].w = 1;
    }
}