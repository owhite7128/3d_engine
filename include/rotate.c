#include "rotate.h"
#include "model.h"
#include "vect.h"
#include <math.h>
#include <stdio.h>


void rotate_mod(MODEL *init_model, ANG3D rot) {
    norm_ang_quat(&rot);

    float x_bar = 0, y_bar = 0, z_bar = 0;
    for(int l = 1; l < ((int)init_model->vecs[0].i + 1); l++) {
        x_bar += init_model->vecs[l].i;
        y_bar += init_model->vecs[l].j;
        z_bar += init_model->vecs[l].k;
    }
    x_bar /= init_model->vecs[0].i;
    y_bar /= init_model->vecs[0].i;
    z_bar /= init_model->vecs[0].i;

    float xx = rot.x * rot.x, yy = rot.y * rot.y, zz = rot.z * rot.z;
    float xy = rot.x * rot.y, xz = rot.x * rot.z, yz = rot.y * rot.z;
    float wx = rot.w * rot.x, wy = rot.w * rot.y, wz = rot.w * rot.z;

    float m[3][3] = {
        {1 - 2*(yy + zz), 2*(xy - wz),     2*(xz + wy)},
        {2*(xy + wz),     1 - 2*(xx + zz), 2*(yz - wx)},
        {2*(xz - wy),     2*(yz + wx),     1 - 2*(xx + yy)}
    };

    for (int l = 1; l < ((int)init_model->vecs[0].i + 1); l++) {
        float temp_x = init_model->vecs[l].i - x_bar;
        float temp_y = init_model->vecs[l].j - y_bar;
        float temp_z = init_model->vecs[l].k - z_bar;

        init_model->rot_vecs[l].i = m[0][0]*temp_x + m[0][1]*temp_y + m[0][2]*temp_z + x_bar;
        init_model->rot_vecs[l].j = m[1][0]*temp_x + m[1][1]*temp_y + m[1][2]*temp_z + y_bar;
        init_model->rot_vecs[l].k = m[2][0]*temp_x + m[2][1]*temp_y + m[2][2]*temp_z + z_bar;
        init_model->rot_vecs[l].w = 1;
    }
}