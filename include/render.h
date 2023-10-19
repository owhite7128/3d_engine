#ifndef RENDER_H
#define RENDER_H

#include "model.h"
#include "vect.h"
#include "camera.h"
#include <SDL2/SDL.h>

#define RENDER_MODE_3D 0
#define RENDER_MODE_2D 1

#define SCREEN_HEIGHT 720 
#define SCREEN_WIDTH 1280

#define FMAX 10000000000.0

typedef struct buffer_2d {
    int buff_sz[2];
    char* buffer;
} BUFFER_2D;

typedef struct window_app{
    SDL_Window *window;
    SDL_Texture *texture;
    SDL_Renderer *renderer;
    uint32_t pixels[SCREEN_WIDTH * SCREEN_HEIGHT];
    float depth_buff[SCREEN_WIDTH * SCREEN_HEIGHT];
    void (*init)(struct window_app*); 
    void (*rend)(struct window_app*);
    MODEL_LIST* mod_list;
    CAMERA cam;

    int8_t quit;
} WINDOW_APP;

void render_init (void (*init)(), void (*rend)());

void render (int render_mode);

#endif