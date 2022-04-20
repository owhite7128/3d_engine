#include "import_file.h"
#include <stdlib.h>
#include <stdio.h>

int size_of_file (unsigned char* raw_file) {
    int size;
    int i = 0;

    while (raw_file[i] != '\0') {
        size = i;
        i++;
    }

    return (size);
}


unsigned char* import (char* filename){
    int sz;
    FILE *in_file = fopen (filename, "rb");

    if (in_file == NULL) {
        printf("Invalid File: %s\n",filename);
        exit(-1);
    }

    fseek (in_file, 0L, SEEK_END);
    sz = ftell(in_file);
    rewind(in_file);

    unsigned char *buffer = (char*) malloc(sz*sizeof(char));
    fread(buffer, 1, sz, in_file);

    return buffer;
}
