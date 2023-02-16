#include "model.h"
#include <math.h>
#include <stdlib.h>

void destroy_model (MODEL model) {
    free(model.edgs);
    free(model.tris);
    free(model.tvecs);
    free(model.vecs);
    return;
}