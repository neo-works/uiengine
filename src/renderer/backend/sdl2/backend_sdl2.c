#include "../../../../include/renderer/renderer.h"
#include "../../../../include/mem/mem.h"
#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH    640
#define SCREEN_HEIGHT   480

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

void sdl2_backend_default_draw_rect(RenderBackend *sdl2, Position pos, Size size, Color backgroundColor) {
    for (uint32_t y = pos.y; y < (pos.y + size.height); y++) {
        for (uint32_t x = pos.x; x < (pos.x + size.width); x++) {
            /* TODO */
        }
    }
}

void sdl2_backend_default_init(struct RenderBackend *sdl2) {
    printf("sdl2: init\n");
    if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    } else {
        gWindow = SDL_CreateWindow( "UI demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if (gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
    SDL_UpdateWindowSurface(gWindow);

    SDL_Event e;
    uint16_t close = 0;
    while (close == 0) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                close = 1; 
            }
        }
    }

    return;
}

RenderBackend *backend_sdl2_create() {
    RenderBackend *sdl2  = (RenderBackend *)mem_alloc(sizeof(RenderBackend));
    sdl2->drawRect = sdl2_backend_default_draw_rect;
    sdl2->init = sdl2_backend_default_init;
    return sdl2;
}