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

#define PI 3.14159265358

float t = 0.0;
int y = -1;

void on_init_rend (WINDOW_APP* app) {
    /*VEC3D mod_vec = {0, 0, -7, 1};
    ANG3D mod_ang = {PI/2, 0, 0, 0};
    add_model (app->mod_list, "./spheretris.obj", mod_vec, mod_ang, 1);*/

    VEC3D mod_vec_2 = {0, 0, -20, 1};
    ANG3D mod_ang_2 = {0, PI, 0, 0.1};
    add_model (app->mod_list, "./monkey.obj", mod_vec_2, mod_ang_2, 1);

    /*VEC3D mod_vec_3 = {-2, 0, -7, 1};
    ANG3D mod_ang_3 = {PI/2, 0, 0, 0.1};
    add_model (app->mod_list, "./monkey.obj", mod_vec_3, mod_ang_3, 1);*/

    /*VEC3D mod_vec_4 = {2, 0, -7, 1};
    ANG3D mod_ang_4 = {PI/2, 0, 0, 0};
    add_model (app->mod_list, "./monkey.obj", mod_vec_4, mod_ang_4, 1);*/
    
    return;
}

// ANG3D mod_rot = {0, PI/2, 0, 0.01};
void call_rend (WINDOW_APP* app) {
    ANG3D mod_rot = {0, PI, 0, t};
    VEC3D mod_mov = {0, 0, -7-5-5*sin(t), 1};
    set_model_rot (app->mod_list->head->curr, mod_rot);
    set_model_pos (app->mod_list->head->curr, mod_mov);
    /*set_model_rot (app->mod_list->head->next->curr, mod_rot);
    set_model_rot (app->mod_list->head->next->next->curr, mod_rot);*/
    //printf ("Z Rot: %f\n", app->mod_list->head->curr->rot.z);
    // VEC3D mod_mov = {0, y, -7, 1};
    // VEC3D mod_mov = {0, 0, y, 1};
    //set_model_pos (app->mod_list->head->curr, mod_mov);
    // ANG3D cam_rot = {0, 0, t, 1};
    // update_camera_ang (&(app->cam), cam_rot);

    //printf ("T: %f\n", t);
    if (t >= 2*PI)
    {
        t = 0;
    } else {
        t += PI/128;
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