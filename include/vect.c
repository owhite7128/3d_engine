#include "vect.h"
#include <stdlib.h>

// Figure out actual freeing of Memory
void mod_free (MODEL model){
    free(model.vecs);
    free(model.edgs);
    free(model.tris);
}