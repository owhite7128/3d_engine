#include "../include/transform.h"
#include "../include/vect.h"
#include "../include/model.h"
#include "../include/import_obj.h"
#include "../include/camera.h"
#include "../include/rotate.h"
#include "../include/render.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define PI 3.14159265358765

float t = 0.0;
int y = -7;

void on_init_rend (WINDOW_APP* app) {
    /*VEC3D mod_vec = {0, 0, 0, 1};
    ANG3D mod_ang = {PI/2, 0, 0, 0};
    add_model (app->mod_list, "./sphere.obj", mod_vec, mod_ang, 1);*/

    VEC3D mod_vec_2 = {0, 0, -7, 1};
    ANG3D mod_ang_2 = {PI/2, 0, 0, 0};
    add_model (app->mod_list, "./monkey.obj", mod_vec_2, mod_ang_2, 1);

    /*VEC3D mod_vec_3 = {-2, 0, -7, 1};
    ANG3D mod_ang_3 = {PI/2, 0, 0, 0};
    add_model (app->mod_list, "./monkey.obj", mod_vec_3, mod_ang_3, 1);

    VEC3D mod_vec_4 = {2, 0, -7, 1};
    ANG3D mod_ang_4 = {PI/2, 0, 0, 0};
    add_model (app->mod_list, "./monkey.obj", mod_vec_4, mod_ang_4, 1);*/
    
    return;
}

// ANG3D mod_rot = {0, PI/2, 0, 0.01};
void call_rend (WINDOW_APP* app) {
    
    // ANG3D mod_rot = {0, PI/4, 0, 1};
    // VEC3D mod_mov = {(int) -4*cos(t), 0, 0, 1};
    // VEC3D mod_mov = {0, 0, y, 1};
    // set_model (app->mod_list->head->curr, mod_mov);
    // ANG3D cam_rot = {0, 0, t, 1};
    // update_camera_ang (&(app->cam), cam_rot);
    // rotate_mod (app->mod_list->head->curr, mod_rot);

    if (y == -24)
    {
        y = -7;
    } else {
        y -= 1;
    }

    if (t >= 2*PI)
    {
        t = 0;
    } else {
        t += PI/256;
    }
    return;
}

int main (int argc, char** argv) {
    int status;
    srand(time(NULL));

    render_init (on_init_rend, call_rend);
    render (RENDER_MODE_3D);
    return 0;
}