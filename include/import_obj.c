#include "import_obj.h"
#include "vect.h"
#include "model.h"
#include <stdio.h>
#include <stdlib.h>

int COLORS[6] = {0xFFFF0000, 0xFF00FF00, 0xFF0000FF, 0xFFFFFF00, 0xFF00FFFF, 0xFFFF00FF};

/* 
    only need v and f
    can disregard vt and vn
    as well as s and o and mtllib
*/
// v x y z
// f v1/vt/vn v2/vt/vn v3/vt/vn v4/vt/vn
// Should I disregard edges? Just Send the Faces 
// Pros: Easier to jump to face colors
// Cons: Have to completely redo the output main

// For now just going to work out verticies
MODEL* import_model (char* filename, int model_type) {
    if(model_type == 0){
    FILE* in_file = fopen(filename, "rb");
    char* buffer = NULL;
    MODEL *in_model;
    in_model = (MODEL*) malloc (1*sizeof(MODEL));
    in_model->id = 0;

    if (in_file == NULL) {
        printf ("ERR: Invalid Filename\n");
        exit(-1);
    }
    fseek(in_file, 0L, SEEK_END);
    int sz = ftell(in_file);
    rewind(in_file);

    buffer = (char*) malloc(sz*sizeof(char));
    fread(buffer, 1, sz, in_file);


    //in_model->faces = create_faces (buffer, sz);
    in_model->vecs = create_vecs (buffer, sz);
    in_model->tvecs = (VEC2D*) malloc(((int)in_model->vecs[0].i +1)*sizeof(VEC2D));
    in_model->tris = create_tris (buffer, sz);

    in_model->rot_vecs = (VEC3D*) malloc(((int)in_model->vecs[0].i +1)*sizeof(VEC3D));

    return in_model;
    }
    else {
        printf ("ERR model unsupported\n");
        exit (-1);
    }
}

VEC3D* create_vecs (char* file_buffer, int sz) {
    VEC3D *vecs = NULL;
    int vec_count = 0;
    int vec_idx = 1;
    char* temp;

    for (int i=0; i<sz; i++) {
        if (file_buffer[i] == 'v' && file_buffer[i+1] == ' ' && file_buffer[i-1] == '\n') {
            vec_count++;
        }
    }

    vecs = (VEC3D*) malloc ((vec_count+1)*sizeof(VEC3D));
    vecs[0].i = vec_count;
    for (int i=0; i<sz; i++) {
        if (file_buffer[i] == 'v' && file_buffer[i+1] == ' ' && file_buffer[i-1] == '\n') {
            int j = 2;
            int temp_idx = 0;
            for (int q=0; q<3; q++) {
                temp = (char*) calloc(100, sizeof(char));
                while(!(file_buffer[i+j+temp_idx] == ' ' || file_buffer[i+j+temp_idx] == '\n')) {
                    temp[temp_idx] = file_buffer[i+j+temp_idx];
                    temp_idx++;
                }
                switch(q) {
                    case 0:
                        vecs[vec_idx].i = atof(temp);
                    case 1:
                        vecs[vec_idx].j = atof(temp);
                    case 2:
                        vecs[vec_idx].k = atof(temp);
                }

                vecs[vec_idx].w = 0;
                j += temp_idx + 1;
                temp_idx = 0;
                free(temp);
                temp = NULL;
            }
            vec_idx++;
        }
    }
    return vecs;
}

// Do triangle creation
TRIANG* create_tris (char* file_buffer, int sz)
{
    TRIANG *tris = NULL;
    int tri_cnt = 0;
    int tri_idx = 1;
    char* temp;

    for (int i=0; i<sz; i++) {
        if (file_buffer[i] == 'f' && file_buffer[i+1] == ' ' && file_buffer[i-1] == '\n') {
            tri_cnt++;
        }
    }

    tris = (TRIANG*) malloc ((tri_cnt+1)*sizeof(TRIANG));
    tris[0].s = tri_cnt;

    for (int i=0; i<sz; i++) {
        if (file_buffer[i] == 'f' && file_buffer[i+1] == ' ' && file_buffer[i-1] == '\n') {
            int j = 2;
            int slash_idx = 0;
            int space_idx = 0;
            for (int q=0; q<3; q++) {
                temp = (char*) calloc (100, sizeof(char));
                while (!(file_buffer[i+j+space_idx] == ' ' || file_buffer[i+j+space_idx] == '\n')) {
                    if (file_buffer[i+j+slash_idx] != '/') {
                        temp[slash_idx] = file_buffer[i+j+slash_idx];
                        slash_idx++;
                    }
                    space_idx++;
                }
                switch (q) {
                    case 0:
                        tris[tri_idx].s = atoi(temp);
                    case 1:
                        tris[tri_idx].m = atoi(temp);
                    case 2:
                        tris[tri_idx].e = atoi(temp);
                }
                /*if (face_idx % 2 == 0) {
                    faces[face_idx].draw = 1;
                }else {
                    faces[face_idx].draw = 0;
                }*/
                //tris[face_idx].draw = 1;

                tris[tri_idx].color = COLORS[rand() % 6];

                j += space_idx + 1;
                space_idx = 0;
                slash_idx = 0;
                free(temp);
                temp = NULL;
            }
            tri_idx++;
        }
    }
    return tris;
}

FACE* create_faces (char* file_buffer, int sz) {
    FACE *faces = NULL;
    int face_count = 0;
    int face_idx = 1;
    char* temp;

    for (int i=0; i<sz; i++) {
        if (file_buffer[i] == 'f' && file_buffer[i+1] == ' ' && file_buffer[i-1] == '\n') {
            face_count++;
        }
    }

    faces = (FACE*) malloc ((face_count+1)*sizeof(FACE));
    faces[0].one = face_count;


    for (int i=0; i<sz; i++) {
        if (file_buffer[i] == 'f' && file_buffer[i+1] == ' ' && file_buffer[i-1] == '\n') {
            int j = 2;
            int slash_idx = 0;
            int space_idx = 0;
            for (int q=0; q<4; q++) {
                temp = (char*) calloc (100, sizeof(char));
                while (!(file_buffer[i+j+space_idx] == ' ' || file_buffer[i+j+space_idx] == '\n')) {
                    if (file_buffer[i+j+slash_idx] != '/') {
                        temp[slash_idx] = file_buffer[i+j+slash_idx];
                        slash_idx++;
                    }
                    space_idx++;
                }
                switch (q) {
                    case 0:
                        faces[face_idx].one = atoi(temp);
                    case 1:
                        faces[face_idx].two = atoi(temp);
                    case 2:
                        faces[face_idx].three = atoi(temp);
                    case 3:
                        faces[face_idx].four = atoi(temp);
                }
                /*if (face_idx % 2 == 0) {
                    faces[face_idx].draw = 1;
                }else {
                    faces[face_idx].draw = 0;
                }*/
                faces[face_idx].draw = 1;


                j += space_idx + 1;
                space_idx = 0;
                slash_idx = 0;
                free(temp);
                temp = NULL;
            }
            face_idx++;
        }
    }
    return faces;
}
