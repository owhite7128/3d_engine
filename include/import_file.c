#include "import_file.h"
#include "vect.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int size_of_file (unsigned char* raw_file) {
    int size;
    int i = 0;

    while (raw_file[i] != '\0') {
        size = i;
        i++;
    }

    return (size);
}

VEC3D* mod_import_vects (char* filename){
    int sz;
    int amnt = 0;
    FILE *in_file = fopen (filename, "rb");

    if (in_file == NULL) {
        printf("Invalid File: %s\n",filename);
        exit(-1);
    }

    fseek (in_file, 0L, SEEK_END);
    sz = ftell(in_file);
    rewind(in_file);

    char *buffer = (char*) malloc(sz*sizeof(char));
    fread(buffer, 1, sz, in_file);

    for (int i=0; i<sz;i++) {
        if(buffer[i] == '\n' && buffer[i-1] == 'V' && buffer[i-2] == '#' && buffer[i-3] == '#'){
            int end = 0;
            int j = i+1;
            while (!end) {
                if(buffer[j] == '\n' && buffer[j+1] == '\n') {
                    amnt++;
                    end = 1;
                }else if (buffer[j] == '\n')
                {
                    amnt++;
                }
                
                j++;
            }
        }
    }

    VEC3D *pts = (VEC3D*) malloc((amnt+1)*sizeof(VEC3D));
    pts[0].i = amnt;
    pts[0].j = 0;
    pts[0].k = 0;
    pts[0].w = -1;

    for(int l=0; l<sz;l++) {
        if(buffer[l] == '#' && buffer[l+1] == '#'){
            if(buffer[l+2] == 'V' ){
                int end = 0;
                int q = l+4;
                int pt = 1;
                while (!end) {
                    if(buffer[q] == '\n' && buffer[q+1] == '\n'){
                        end = 1;
                    }else if (buffer[q] == '(')
                    {
                        int n=1;
                        int m=0;
                        int b=0;
                        char temp[5];
                        temp[4] = '\0';
                        while (buffer[q+n] != ',') {
                            temp[n-1] = buffer[q+n];
                            n++;
                        }
                        pts[pt].i = strtod(temp,NULL);
                        n++;
                        while (buffer[q+n+m] != ',') {
                            temp[m] = buffer[q+n+m];
                            m++;
                        }
                        m++;
                        pts[pt].j = strtod(temp,NULL);
                        while (buffer[q+n+m+b] != ')') {
                            temp[b] = buffer[q+n+m+b];
                            b++;
                        }
                        pts[pt].k = strtod(temp,NULL);

                        pts[pt].w = 1;
                        pt++;
                    } 
                    q++;
                }
            }
        }
    }

    free(buffer);
    return pts;
}

EDGE* mod_import_edges (char* filename){
    int sz;
    int amnt = 0;
    FILE *in_file = fopen (filename, "rb");

    if (in_file == NULL) {
        printf("Invalid File: %s\n",filename);
        exit(-1);
    }

    fseek (in_file, 0L, SEEK_END);
    sz = ftell(in_file);
    rewind(in_file);

    char *buffer = (char*) malloc(sz*sizeof(char));
    fread(buffer, 1, sz, in_file);

    for (int i=0; i<sz;i++) {
        if(buffer[i] == '\n' && buffer[i-1] == 'E' && buffer[i-2] == '#' && buffer[i-3] == '#'){
            int end = 0;
            int j = i+1;
            while (!end) {
                if(buffer[j] == '\n' && buffer[j+1] == '\n') {
                    amnt++;
                    end = 1;
                }else if (buffer[j] == '\n')
                {
                    amnt++;
                }
                
                j++;
            }
        }
    }

    EDGE *edgs = (EDGE*) malloc((amnt+1)*sizeof(EDGE));
    edgs[0].s = amnt;
    edgs[0].e = 0;

    for(int l=0; l<sz;l++) {
        if(buffer[l] == '#' && buffer[l+1] == '#'){
            if(buffer[l+2] == 'E' ){
                int end = 0;
                int q = l+4;
                int edg = 1;
                while (!end) {
                    if(buffer[q] == '\n' && buffer[q+1] == '\n'){
                        end = 1;
                    }else if (buffer[q] == '(')
                    {
                        int n=1;
                        int m=0;
                        char temp[5];
                        temp[4] = '\0';
                        while (buffer[q+n] != ',') {
                            temp[n-1] = buffer[q+n];
                            n++;
                        }
                        edgs[edg].s = strtod(temp,NULL);
                        n++;
                        while (buffer[q+n+m] != ')') {
                            temp[m] = buffer[q+n+m];
                            m++;
                        }
                        edgs[edg].e = strtod(temp,NULL);
                        edg++;
                    } 
                    q++;
                }
            }
        }
    }

    free(buffer);
    return edgs;
}

TRIANG* mod_import_tris (char* filename){
    int sz;
    int amnt = 0;
    FILE *in_file = fopen (filename, "rb");

    if (in_file == NULL) {
        printf("Invalid File: %s\n",filename);
        exit(-1);
    }

    fseek (in_file, 0L, SEEK_END);
    sz = ftell(in_file);
    rewind(in_file);

    char *buffer = (char*) malloc(sz*sizeof(char));
    fread(buffer, 1, sz, in_file);

    for (int i=0; i<sz;i++) {
        if(buffer[i] == '\n' && buffer[i-1] == 'F' && buffer[i-2] == '#' && buffer[i-3] == '#'){
            int end = 0;
            int j = i+1;
            while (!end) {
                if(buffer[j] == '\n' && buffer[j+1] == '\n') {
                    amnt++;
                    end = 1;
                }else if (buffer[j] == '\n')
                {
                    amnt++;
                }
                
                j++;
            }
        }
    }

    TRIANG *tris = (TRIANG*) malloc((amnt+1)*sizeof(TRIANG));
    tris[0].s = amnt;
    tris[0].m = 0;
    tris[0].e = 0;

    for(int l=0; l<sz;l++) {
        if(buffer[l] == '#' && buffer[l+1] == '#'){
            if(buffer[l+2] == 'F' ){
                int end = 0;
                int q = l+4;
                int tri = 1;
                while (!end) {
                    if(buffer[q] == '\n' && buffer[q+1] == '\n'){
                        end = 1;
                    }else if (buffer[q] == '(')
                    {
                        int n=1;
                        int m=0;
                        int b=0;
                        char temp[5];
                        temp[4] = '\0';
                        while (buffer[q+n] != ',') {
                            temp[n-1] = buffer[q+n];
                            n++;
                        }
                        tris[tri].s = strtod(temp,NULL);
                        n++;
                        while (buffer[q+n+m] != ',') {
                            temp[m] = buffer[q+n+m];
                            m++;
                        }
                        tris[tri].m = strtod(temp,NULL);
                        m++;
                        while (buffer[q+n+m+b] != ')') {
                            temp[b] = buffer[q+n+m+b];
                            b++;
                        }
                        tris[tri].e = strtod(temp,NULL);
                        tri++;
                    } 
                    q++;
                }
            }
        }
    }

    free(buffer);
    return tris;
}

MODEL mod_import(char* filename) {
    MODEL model;
    model.id = 0;
    model.vecs = mod_import_vects(filename);
    model.edgs = mod_import_edges(filename);
    model.tris = mod_import_tris(filename);

    return model;
}