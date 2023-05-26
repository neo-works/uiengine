#include "../../../../include/renderer/renderer.h"
#include "../../../../include/mem/mem.h"
#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH    640
#define SCREEN_HEIGHT   480

SDL_Window* gWindow = NULL;
SDL_Renderer *sdlRenderer = NULL;

void sdl2_backend_default_draw_rect(RenderBackend *sdl2, Position pos, Size size, Color backgroundColor) {
    SDL_SetRenderDrawColor(sdlRenderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_Rect rect = {
        pos.x, pos.y, size.width, size.height
    };
    SDL_RenderFillRect(sdlRenderer, &rect);
}

void sdl2_backend_default_init(struct RenderBackend *sdl2) {
    printf("sdl2: init\n");
    if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    gWindow = SDL_CreateWindow( "UI demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if (gWindow == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    sdlRenderer = SDL_CreateRenderer(gWindow, -1, 0);
    if (sdlRenderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    return;
}

void sdl2_backend_default_submit(RenderBackend *sdl2) {
    SDL_RenderPresent(sdlRenderer);
}

void sdl2_backend_default_clear(RenderBackend *sdl2) {
    SDL_RenderClear(sdlRenderer);
}

int sdl2_backend_default_polling(RenderBackend *sdl2) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            return 1; 
        }
    }
    return 0;
}

RenderBackend *backend_sdl2_create() {
    RenderBackend *sdl2  = (RenderBackend *)mem_alloc(sizeof(RenderBackend));
    sdl2->drawRect = sdl2_backend_default_draw_rect;
    sdl2->submit = sdl2_backend_default_submit;
    sdl2->clear = sdl2_backend_default_clear;
    sdl2->polling = sdl2_backend_default_polling;
    sdl2->init = sdl2_backend_default_init;
    return sdl2;
}