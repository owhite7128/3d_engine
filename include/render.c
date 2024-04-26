#include "render.h"
#include "vect.h"
#include "camera.h"
#include "model.h"
#include "rotate.h"
#include "transform.h"
#include "import_obj.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <SDL2/SDL.h>


/* 
    Primary Goal is to get one unifed render function that calls everything that needs to happen
    Need to have some sort of models list for everything that is loaded. 
    Create object function adds to the list.
    Delete object removes from the list.

    Once render is called freeze the list and make the checks for rendered planes.
    Then only convert the rendered planes into 2d planes.
*/

WINDOW_APP state;


// Want Z-Buff to do Z-Culling. Get that as model_tfrm is happening. Also grab color (later)
int intersect_tri (VEC3D v1, VEC3D v2, VEC3D v3, VEC3D pt, VEC3D vec)
{
    // Build plane
    VEC3D one = vec3_sub (v2, v1);
    VEC3D two = vec3_sub (v3, v1);

    VEC3D cross = vec_cross (one, two);
    VEC3D zero_vec = {0, 0, 0, 0};
    VEC3D plane_norm = vec3_norm (cross, vec3_len(zero_vec, cross));

    float d = vec3_dot (plane_norm, v1);

    float plane_vec_dot = vec3_dot(plane_norm, vec);

    if (plane_vec_dot <= 0.001 && plane_vec_dot >= -0.001)
    {
        return 0;
    }
    if (plane_vec_dot < 0) {
        plane_norm.i = -plane_norm.i;
        plane_norm.j = -plane_norm.j;
        plane_norm.k = -plane_norm.k;
    }
    if (vec3_dot(vec_cross(vec3_sub(v2, v1), vec3_sub(vec, v1)), plane_norm) >= 0)
    {
        return 0;
    }
    if (vec3_dot(vec_cross(vec3_sub(v3, v2), vec3_sub(vec, v2)), plane_norm) >= 0)
    {
        return 0;
    }
    if (vec3_dot(vec_cross(vec3_sub(v1, v3), vec3_sub(vec, v3)), plane_norm) >= 0)
    {
        return 0;
    }
    return 1;
}

// Should this raycast?
void check_occlusion (MODEL* check_mod, float* z_buff) {
    int tri_len = check_mod->tris[0].s;
    VEC3D comp_vec;
    VEC3D zero_vec;
    zero_vec.i = 0;
    zero_vec.j = 0;
    zero_vec.k = 0;
    zero_vec.w = 1;

    for (int q=1; q<tri_len+1; q++)
    {
        check_mod->tris[q].draw = 1;
        //int cent_x = (check_mod.vecs[check_mod.tris[q].s].i + check_mod.vecs[check_mod.tris[q].m].i + check_mod.vecs[check_mod.tris[q].e].i) / 3;
        //int cent_y = (check_mod.vecs[check_mod.tris[q].s].j + check_mod.vecs[check_mod.tris[q].m].j + check_mod.vecs[check_mod.tris[q].e].j) / 3;
        /*int cent_z = (check_mod->vecs[check_mod->tris[q].s].k + check_mod->vecs[check_mod->tris[q].m].k + check_mod->vecs[check_mod->tris[q].e].k) / 3;
        
        for (int l=0; l<SCREEN_HEIGHT; l+=5)
        {
            for (int m=0; m<SCREEN_WIDTH; m+=5)
            {
                comp_vec.i = m;
                comp_vec.j = l;
                comp_vec.k = state.cam.drwpln.k;
                if (intersect_tri(check_mod->vecs[check_mod->tris[q].s], check_mod->vecs[check_mod->tris[q].m], check_mod->vecs[check_mod->tris[q].e], zero_vec, comp_vec))
            {
                if (state.depth_buff[(l*SCREEN_WIDTH + m)] >= cent_z)
                {
                    state.depth_buff[(l*SCREEN_WIDTH + m)] = cent_z;
                }
                else {
                   check_mod->tris[q].draw = 0; 
                }
            }

            }
        }*/

        /*for (int l=0; l<SCREEN_HEIGHT*SCREEN_WIDTH; l++)
        {

            // Building vectors to raycast for mod_buff
            comp_vec.i = l % SCREEN_WIDTH;
            comp_vec.j = (float)((int) l / SCREEN_WIDTH);
            comp_vec.k = state.cam.drwpln.k;

            if (intersect_tri(check_mod->vecs[check_mod->tris[q].s], check_mod->vecs[check_mod->tris[q].m], check_mod->vecs[check_mod->tris[q].e], zero_vec, comp_vec))
            {
                if (state.depth_buff[l] >= cent_z)
                {
                    state.depth_buff[l] = cent_z;
                }
                else {
                   check_mod->tris[q].draw = 0; 
                }
            }
        }*/
    }
    return;
}


float sign (VEC2D pt, VEC2D v1, VEC2D v2)
{
    return (pt.i - v2.i) * (v1.j - v2.j) - (v1.i - v2.i) * (pt.j - v2.j);
}

int pt_in_tri (VEC2D pt, VEC2D v1, VEC2D v2, VEC2D v3)
{
    float d1, d2, d3;
    int has_neg, has_pos;

    d1 = sign (pt, v1, v2);
    d2 = sign (pt, v2, v3);
    d3 = sign (pt, v3, v1);

    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

float calcZ(VEC3D p1, VEC3D p2, VEC3D p3, float x, float y) {
    float det = (p2.j - p3.j) * (p1.i - p3.i) + (p3.i - p2.i) * (p1.j - p3.j);

    float l1 = ((p2.j - p3.j) * (x - p3.i) + (p3.i - p2.i) * (y - p3.j)) / det;
    float l2 = ((p3.j - p1.j) * (x - p3.i) + (p1.i - p3.i) * (y - p3.j)) / det;
    float l3 = 1.0f - l1 - l2;

    return l1 * p1.k + l2 * p2.k + l3 * p3.k;
}

void swap_vec2d (VEC2D *a, VEC2D *b)
{
    VEC2D temp;
    temp.i = a->i;
    temp.j = a->j;
    temp.k = a->k;

    a->i = b->i;
    a->j = b->j;
    a->k = b->k;

    b->i = temp.i;
    b->j = temp.j;
    b->k = temp.k;
}


void render_tri (uint32_t *cbuff, float *zbuff, MODEL* mod, TRIANG tri) {
    VEC2D v1 = mod->tvecs[tri.s];
    VEC2D v2 = mod->tvecs[tri.m];
    VEC2D v3 = mod->tvecs[tri.e];

    int half_height = SCREEN_HEIGHT / 2;
    int half_width = SCREEN_WIDTH / 2;

    int min_x = 100000000;
    int min_y = 100000000;
    int max_x = 0;
    int max_y = 0;


    if (v1.i + half_width > max_x)
    {
        max_x = v1.i+ half_width;
    }
    if (v1.i + half_width < min_x)
    {
        min_x = v1.i + half_width;
    }
    if (v1.j + half_height > max_y)
    {
        max_y = v1.j + half_height;
    }
    if (v1.j + half_height < min_y)
    {
        min_y = v1.j + half_height;
    }

    if (v2.i + half_width > max_x)
    {
        max_x = v2.i + half_width;
    }
    if (v2.i + half_width < min_x)
    {
        min_x = v2.i + half_width;
    }
    if (v2.j + half_height > max_y)
    {
        max_y = v2.j + half_height;
    }
    if (v2.j + half_height < min_y)
    {
        min_y = v2.j + half_height;
    }

    if (v3.i + half_width > max_x)
    {
        max_x = v3.i + half_width;
    }
    if (v3.i + half_width < min_x)
    {
        min_x = v3.i + half_width;
    }
    if (v3.j + half_height > max_y)
    {
        max_y = v3.j + half_height;
    }
    if (v3.j + half_height < min_y)
    {
        min_y = v3.j + half_height;
    }
    
    int p1 = tri.s;
    int p2 = tri.m;
    int p3 = tri.e;
    int temp;

    VEC3D A = {mod->rot_vecs[p2].i - mod->rot_vecs[p1].i, mod->rot_vecs[p2].j - mod->rot_vecs[p1].j, mod->rot_vecs[p2].k - mod->rot_vecs[p1].k, 1};
    VEC3D B = {mod->rot_vecs[p3].i - mod->rot_vecs[p1].i, mod->rot_vecs[p3].j - mod->rot_vecs[p1].j, mod->rot_vecs[p3].k - mod->rot_vecs[p1].k, 1};
    VEC3D C = {mod->rot_vecs[p2].i - 0 + mod->pos.i, mod->rot_vecs[p2].j - 0 + mod->pos.j, mod->rot_vecs[p2].k - 0 + mod->pos.k, 1};

    VEC3D CROSS = vec_cross(A, B);
    VEC3D zero_vec = {0, 0, 0 , 1};
    VEC3D NORM = vec3_norm(CROSS, vec3_len(zero_vec, CROSS));
   
    if (vec3_dot(NORM, C) < 0)
    {
        NORM = vec3_sub(zero_vec, NORM);

    }

    NORM.w = NORM.i*mod->rot_vecs[p1].i + NORM.j*mod->rot_vecs[p1].j + NORM.k*mod->rot_vecs[p1].k;

    for (int i=min_y; i<max_y; i++)
    {
        for (int j=min_x; j<max_x; j++)
        {
            VEC2D pt_vec = {j-half_width, i-half_height, 1};
            if (pt_in_tri(pt_vec, v1, v2, v3))
            {
                //float zval = calcZ(mod->vecs[p1], mod->vecs[p2], mod->vecs[p3], pt_vec.i, pt_vec.j);
                float tval = NORM.w/(NORM.i*(j-half_width) + NORM.j*(i-half_height) + NORM.k*(state.cam.drwpln.k));
                float zval = (state.cam.drwpln.k)*tval;
                if (i >= 0 && i < SCREEN_HEIGHT && j >= 0 && j < SCREEN_WIDTH){
                    if (zbuff[i*SCREEN_WIDTH+j] < zval)
                    {
                        cbuff[i*SCREEN_WIDTH + j] = tri.color;
                        zbuff[i*SCREEN_WIDTH + j] = zval;
                    }
                } 
            }
        }

    }
}

void draw_3d (uint32_t *cbuff, float *zbuff, MODEL *mod, CAMERA cam) {
    clock_t a = clock();

    for (int m=1; m<mod->tris[0].s + 1; m++)
    {
        render_tri (cbuff, zbuff, mod, mod->tris[m]);
    }
    clock_t b = clock();
    double time_spent = (double)(b - a) / CLOCKS_PER_SEC;
    printf ("\tTime for Drawing Tris: %lf\n", time_spent);
}
void clear_buffer (BUFFER_2D buff)
{
    for (int i=0; i<buff.buff_sz[1]; i++)
    {
        for (int j=0; j<buff.buff_sz[0]; j++)
        {
            buff.buffer[(i*buff.buff_sz[0])+j] = ' ';
        }
    }
}

int msleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

void render_init (void (*init)(WINDOW_APP*), void (*rend)(WINDOW_APP*)) 
{
    state.window = SDL_CreateWindow ("DEMO", SDL_WINDOWPOS_CENTERED_DISPLAY(1), SDL_WINDOWPOS_CENTERED_DISPLAY(1), SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    state.renderer = SDL_CreateRenderer (state.window, -1, SDL_RENDERER_PRESENTVSYNC);

    state.texture = SDL_CreateTexture (state.renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

    

    state.mod_list = create_model_list ();
    state.init = init;
    state.rend = rend;

    ANG3D cang;
    cang.x = 0;
    cang.y = 0;
    cang.z = 0;
    cang.w = 0;

    VEC3D cpos;
    cpos.i = 0;
    cpos.j = 0;
    cpos.k = 0;
    cpos.w = 1;

    VEC3D ddist;
    ddist.i = 0;
    ddist.j = 0;
    ddist.k = 734;
    ddist.w = 1;
    
    state.cam = create_camera (cang, cpos, ddist);

    state.init(&state);

    for (int i=0; i<SCREEN_WIDTH*SCREEN_HEIGHT; i++)
    {
        state.depth_buff[i] = FMAX;
    }
}

void render(int render_mode) {
    clock_t t;
    clock_t end;

    if (render_mode == 0)
    {
        while (!state.quit) {
            t = clock();
            SDL_Event ev;
            while (SDL_PollEvent(&ev)) {
                switch (ev.type) {
                    case SDL_QUIT:
                        state.quit = 1;
                        break;
                }
            }
            // Calls the onRender FXN given by FXN Ptr
            state.rend(&state);

            // Clears the Buffers
            memset (state.pixels, 0, sizeof(state.pixels));
            memset (state.depth_buff, -10000000.0, sizeof(state.depth_buff));


            MODEL_NODE* track = state.mod_list->head;
            track = state.mod_list->head;
            while (track != NULL)
            {
                model_tfrm (track->curr, state.cam);
                draw_3d (state.pixels, state.depth_buff, track->curr, state.cam);
                track = track->next;
            }



            SDL_UpdateTexture (state.texture, NULL, state.pixels, SCREEN_WIDTH * 4);
            SDL_RenderCopyEx (state.renderer, state.texture, NULL, NULL, 0.0, NULL, 0);
            SDL_RenderPresent (state.renderer);

            end = clock();
            double time_spent = (double)(end - t) / CLOCKS_PER_SEC;
            printf ("Time Taken: %lf\n", time_spent);
        }
        // while (1) {

            /*
            // Convert to 2D Pts.. after doing occlusion change this to converting face. Can be destructive. Face_list should get free() after render call.
            for (int i=0; i<model_amnt; i++)
            {
                // Check Occlusion of Each Model.
                // if (check_occlusion(model_list[i], ))
                // {
                model_tfrm (&model_list[i], camera);
                // }
                add_to_dbuffer (draw_buffer, model_list[i]);
            }
            draw (draw_buffer);
            */
        // }
        SDL_DestroyWindow (state.window);  
    }else if (render_mode == 1)
    {
        printf ("Unimplemented Feature. 2D Rendering is not Enabled Yet\n");
        exit (0);
    }else
    {
        printf ("ERR Invalid Render Mode\n");
        exit (-1);
    }
}