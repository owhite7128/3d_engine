#include "transform.h"
#include "vect.h"
#include "model.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

VEC2D point_3t2 (VEC3D vec, ANG3D ang, VEC3D cpos, VEC3D ddist) {
    VEC2D p_vec;
    p_vec.k = 1;
    VEC3D rot_vec;
    rot_vec.w = 1;
    
    rot_vec.i = cos(ang.y) * (sin(ang.z) * (vec.j - cpos.j) + cos(ang.z) * (vec.i - cpos.i)) - sin(ang.y) * (vec.k - cpos.k);
    rot_vec.j = sin(ang.x) * (cos(ang.y) * (vec.k - cpos.k)) + sin(ang.y) * (sin(ang.z) * (vec.j - cpos.j) + cos(ang.z) * (vec.i - cpos.i)) + cos(ang.x) * (cos(ang.z) * (vec.j - cpos.j) - sin(ang.z) * (vec.i - cpos.i));
    rot_vec.k = cos(ang.x) * (cos(ang.y) * (vec.k - cpos.k)) + sin(ang.y) * (sin(ang.z) * (vec.j - cpos.j) + cos(ang.z) * (vec.i - cpos.i)) - sin(ang.x) * (cos(ang.z) * (vec.j - cpos.j) - sin(ang.z) * (vec.i - cpos.i));

    p_vec.i = ((ddist.k * rot_vec.i) / (rot_vec.k)) + ddist.i;
    p_vec.j = ((ddist.k * rot_vec.j) / (rot_vec.k)) + ddist.j;

    return p_vec;
}

void model_tfrm (MODEL init_model, ANG3D ang, VEC3D cpos, VEC3D ddist) {
    for(int l=1; l<((int)init_model.vecs[0].i + 1);l++) {
        init_model.tvecs[l] = point_3t2(init_model.vecs[l], ang, cpos, ddist);
    }
}


//ROTATION DOESN'T REALLY WORK
void rotate_mod(MODEL init_model, ANG3D rot) {
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
        float temp_x = init_model.vecs[l].i;
        float temp_y = init_model.vecs[l].j;
        init_model.vecs[l].i = ((init_model.vecs[l].i - x_bar)*cos(rot.y)*cos(rot.z))+((init_model.vecs[l].j - y_bar)*(cos(rot.x)*sin(rot.z)+sin(rot.x)*sin(rot.y)*cos(rot.z)))+((init_model.vecs[l].k - z_bar)*(sin(rot.x)*sin(rot.z)-cos(rot.x)*sin(rot.y)*cos(rot.z))) + x_bar;
        init_model.vecs[l].j = -((temp_x - x_bar)*cos(rot.y)*sin(rot.z))+((init_model.vecs[l].j - y_bar)*(cos(rot.x)*cos(rot.z)-sin(rot.x)*sin(rot.y)*sin(rot.z)))+((init_model.vecs[l].k - z_bar)*(sin(rot.x)*cos(rot.z)+cos(rot.x)*sin(rot.y)*sin(rot.z))) + y_bar;
        init_model.vecs[l].k = ((temp_x - x_bar) * sin(rot.y))-((temp_y - y_bar)*sin(rot.x)*cos(rot.y))+((init_model.vecs[l].k - z_bar)*cos(rot.x)*cos(rot.y)) + z_bar;
        init_model.vecs[l].w = 1; 
    }
}