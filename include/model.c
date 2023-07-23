#include "model.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "import_obj.h"
#include "rotate.h"

void destroy_model (MODEL* model) {
    free(model->edgs);
    free(model->tris);
    free(model->tvecs);
    free(model->vecs);
    free (model);
    return;
}

MODEL_NODE* new_model_node (MODEL* mod)
{
    MODEL_NODE* new_node;
    new_node = (MODEL_NODE*) malloc (1*sizeof(MODEL_NODE));
    new_node->curr = mod;
    new_node->next = NULL;
    return new_node;
}

MODEL_LIST* create_model_list () {
    MODEL_LIST* new_list = (MODEL_LIST*) malloc (1*sizeof(MODEL_LIST));
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->length = 0;
    return new_list;
}

void move_model (MODEL* mod, VEC3D pos)
{
    mod->pos.i += pos.i;
    mod->pos.j += pos.j;
    mod->pos.k += pos.k;
}

void set_model (MODEL* mod, VEC3D pos) {
    mod->pos.i = pos.i;
    mod->pos.j = pos.j;
    mod->pos.k = pos.k;
    mod->pos.w = pos.w;
}

void add_model (MODEL_LIST* mod_list, char* file_name, VEC3D in_pos, ANG3D in_rot, float in_scale) {
    MODEL* new_mod = import_model (file_name, MODEL_IMPORT_OBJ);
    set_model (new_mod, in_pos);
    rotate_mod (new_mod, in_rot);
    new_mod->scale = in_scale;
    MODEL_NODE* new_node = new_model_node (new_mod);
    if (mod_list->tail) {
        mod_list->tail->next = new_node;
        mod_list->tail = new_node;
    } else {
        mod_list->head = new_node;
        mod_list->tail = new_node;
    }

    return;
}
