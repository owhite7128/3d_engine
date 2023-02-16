#include "../include/transform.h"
#include "../include/vect.h"
#include "../include/model.h"
#include "../include/import_obj.h"
#include "../include/camera.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define PI 3.14159265

int main (int argc, char** argv) {
    int status;
    clock_t t;
    t = clock();

    MODEL cube2 = import_model (argv[1]);

    ANG3D cang;
    cang.x = 0;
    cang.y = 0;
    cang.z = 0;
    cang.w = 0;

    VEC3D cpos;
    cpos.i = 1;
    cpos.j = 1;
    cpos.k = -1.5;
    cpos.w = 1;

    VEC3D ddist;
    ddist.i = 0;
    ddist.j = 0;
    ddist.k = 100;
    ddist.w = 1;

    CAMERA *camera = create_camera (cang, cpos, ddist);

    ANG3D rot;
    rot.x = atof(argv[2]);
    rot.y = atof(argv[3]);
    rot.z = atof(argv[4]);
    rot.w = atof(argv[5]);
    rotate_mod(cube2, rot);
    model_tfrm(cube2, *camera);

    //t = clock() - t;
    //double time_take = ((double)t)/CLOCKS_PER_SEC; 
    //printf("Runtime: %f Seconds\n", time_take);

    for (int l=1; l<((int)cube2.vecs[0].i + 1);l++) {
        printf("(%f,%f)\n",cube2.tvecs[l].i,cube2.tvecs[l].j);
    }
    printf(":");
    for (int l=1; l<((int)cube2.faces[0].one + 1);l++){
        printf("(%d,%d,%d,%d,%d)\n",cube2.faces[l].one,cube2.faces[l].two,cube2.faces[l].three,cube2.faces[l].four,cube2.faces[l].draw);
    }

    return 0;
}