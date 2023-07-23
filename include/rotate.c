#include "rotate.h"
#include "model.h"
#include "vect.h"
#include <math.h>
#include <stdio.h>

//ROTATION DOESN'T REALLY WORK
void rotate_mod(MODEL *init_model, ANG3D rot) {
    norm_ang_quat (&rot);
    float x_bar = 0;
    float y_bar = 0;
    float z_bar = 0;

    /*for(int l=1; l<((int)init_model->vecs[0].i + 1); l++) {
        x_bar += init_model->vecs[l].i;
        y_bar += init_model->vecs[l].j;
        z_bar += init_model->vecs[l].k;
    }

    x_bar /= init_model->vecs[0].i;
    y_bar /= init_model->vecs[0].i;
    z_bar /= init_model->vecs[0].i;*/

    for (int l=1; l<((int)init_model->vecs[0].i + 1); l++) {
        float temp_x = init_model->vecs[l].i - x_bar;
        float temp_y = init_model->vecs[l].j - y_bar;
        float temp_z = init_model->vecs[l].k - z_bar;


        init_model->vecs[l].i = (temp_x*(1-2*pow(rot.y,2)-2*pow(rot.z,2))) + (temp_y*((2*rot.x*rot.y)-(2*rot.w*rot.z))) + (temp_z*((2*rot.x*rot.z)+(rot.w*rot.y))) + x_bar;
        init_model->vecs[l].j = (temp_x*((2*rot.x*rot.y)+(2*rot.w*rot.z))) + (temp_y*(1-2*pow(rot.x,2)-2*pow(rot.z,2))) + (temp_z*((2*rot.y*rot.z)-(rot.w*rot.x))) + y_bar;
        init_model->vecs[l].k = (temp_x*((2*rot.x*rot.z)-(rot.w*rot.y))) + (temp_y*((2*rot.y*rot.z)+(rot.w*rot.x))) + (temp_z*(1-2*pow(rot.x,2)-2*pow(rot.y,2))) + z_bar;
        init_model->vecs[l].w = 1;
    }
    
}