#include "../include/import_file.h"
#include "../include/transform.h"
#include "../include/vect.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define PI 3.14




int main (int argc, char** argv) {
    int status;
    clock_t t;
    t = clock();

    MODEL cube = mod_import(argv[1]);

    //cube.vecs = import_vects(argv[1]);
    //cube.edgs = import_edges(argv[1]);
    //cube.tris = import_tris(argv[1]);

    VEC2D *tpts = (VEC2D*) malloc(((int)cube.vecs[0].i+1) * sizeof(VEC2D));
    tpts[0].i = cube.vecs[0].i;
    tpts[0].j = 0;
    tpts[0].k = -1;

    ANG3D cang;
    cang.x = 0;
    cang.y = 0;
    cang.z = 0;

    VEC3D cpos;
    cpos.i = 0;
    cpos.j = 0;
    cpos.k = -1;
    cpos.w = 1;

    VEC3D ddist;
    ddist.i = 0;
    ddist.j = 0;
    ddist.k = 1;
    ddist.w = 1;


    for (int l=1;l<((int)cube.vecs[0].i + 1);l++) {
        tpts[l] = point_3t2(cube.vecs[l], cang, cpos, ddist);
    }

    for (int l=1;l<((int)cube.vecs[0].i + 1);l++) {
        //printf("Pt %d, i: %f, j: %f, k: %f\n", l, (double)file[l].i, (double)file[l].j, (double)file[l].k);
        printf("Tr %d, i: %f, j: %f\n", l, (double)tpts[l].i, (double)tpts[l].j);
    }

    t = clock() - t;
    double time_take = ((double)t)/CLOCKS_PER_SEC; 
    printf("Runtime: %f Seconds\n", time_take);
    return 0;
}