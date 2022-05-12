#include "../include/import_file.h"
#include "../include/transform.h"
#include "../include/vect.h"
#include "../include/model.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define PI 3.14




int main (int argc, char** argv) {
    int status;
    clock_t t;
    t = clock();

    MODEL cube = mod_import(argv[1]);

    ANG3D cang;
    cang.x = 0;
    cang.y = 0;
    cang.z = 0;

    VEC3D cpos;
    cpos.i = 0;
    cpos.j = 0;
    cpos.k = 0;
    cpos.w = 1;

    VEC3D ddist;
    ddist.i = 0;
    ddist.j = 0;
    ddist.k = 1;
    ddist.w = 1;

    ANG3D rot;
    rot.x = atof(argv[2]);
    rot.y = atof(argv[3]);
    rot.z = atof(argv[4]);
    rotate_mod(cube, rot);
    model_tfrm(cube, cang, cpos, ddist);

    //t = clock() - t;
    //double time_take = ((double)t)/CLOCKS_PER_SEC; 
    //printf("Runtime: %f Seconds\n", time_take);

    for (int l=1; l<((int)cube.vecs[0].i + 1);l++) {
        printf("(%f,%f)\n",cube.tvecs[l].i,cube.tvecs[l].j);
    }
    printf(":");
    for (int l=1; l<((int)cube.edgs[0].s + 1);l++){
        printf("(%d,%d)\n",cube.edgs[l].s,cube.edgs[l].e);
    }
    return 0;
}