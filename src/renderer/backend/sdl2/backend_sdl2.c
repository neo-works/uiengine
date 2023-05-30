#include "../../../../include/renderer/renderer.h"
#include "../../../../include/mem/mem.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH    320
#define SCREEN_HEIGHT   380

SDL_Window* gWindow = NULL;
SDL_Renderer *sdlRenderer = NULL;
TTF_Font *gFont = NULL;

SDL_Texture *sdl_font_get_texutre(Color color, char *text) {
    uint32_t key = hash_text(color, text);
}

void sdl_font_set_texutre(Color color, char *text, SDL_Texture *fontTexture) {
    uint32_t key = hash_text(color, text);
}

void sdl2_backend_default_draw_rect(RenderBackend *sdl2, Position pos, Size size, Color borderColor) {
    SDL_SetRenderDrawColor(sdlRenderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_Rect rect = {
        pos.x, pos.y, size.width, size.height
    };
    SDL_RenderDrawRect(sdlRenderer, &rect);
}

void sdl_backend_default_draw_text(RenderBackend *sdl2, Position pos, Size size, Color color, char *text) {
    // TODO: margin for text
    SDL_Rect textQuad = {
        pos.x + 20, pos.y + 10, size.width - 40, size.height - 20
    };

    SDL_Texture *fontTexture = sdl_font_get_texutre(color, text);
    if (fontTexture == NULL) {
        SDL_Color col;
        col.r = color.r;
        col.g = color.g;
        col.b = color.b;
        col.a = color.a;
        fontTexture = SDL_CreateTextureFromSurface(sdlRenderer, TTF_RenderText_Solid(gFont, "button", col));
        if (fontTexture == NULL) {
            printf("TTF: create texture for text '%s' failed!\n", text);
        }
        sdl_font_set_texutre(color, text, fontTexture);
    }
    SDL_RenderCopy(sdlRenderer, fontTexture, NULL, &textQuad);
}

void sdl2_backend_default_fill_rect(RenderBackend *sdl2, Position pos, Size size, Color backgroundColor) {
    SDL_SetRenderDrawColor(sdlRenderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_Rect rect = {
        pos.x, pos.y, size.width, size.height
    };
    SDL_RenderFillRect(sdlRenderer, &rect);
}

void sdl2_backend_default_init(struct RenderBackend *sdl2) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    gWindow = SDL_CreateWindow( "计算器", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if (gWindow == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    sdlRenderer = SDL_CreateRenderer(gWindow, -1, 0);
    if (sdlRenderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    SDL_RenderSetVSync(sdlRenderer, -1);

    if (TTF_Init() < 0) {
        printf("TTF int failed! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    gFont = TTF_OpenFont("./puhui.ttf", 512);
    if (gFont == NULL) {
        printf("TTF open failed! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    return;
}

void sdl2_backend_default_submit(RenderBackend *sdl2) {
    SDL_RenderPresent(sdlRenderer);
}

void sdl2_backend_default_clear(RenderBackend *sdl2) {
    SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 0);
    SDL_RenderClear(sdlRenderer);
}

Event sdl2_backend_default_polling(RenderBackend *sdl2) {
    SDL_Event e;
    Event retE;
    SDL_PollEvent(&e);
    if (e.type == SDL_QUIT) {
        retE.type = EVENT_EXIT;
    } else if (e.type == SDL_MOUSEMOTION) {
        retE.type = EVENT_MOUSE_MOTION;
        retE.mouseMove.x = e.motion.x;
        retE.mouseMove.y = e.motion.y;
    } else if (e.type == SDL_MOUSEBUTTONUP) {
        if (e.button.button == 1) {
            retE.type = EVENT_MOUSE_LEFT_UP;
        }
        retE.leftMouseUp.x = e.button.x;
        retE.leftMouseUp.y = e.button.y;
    } else if (e.type == SDL_MOUSEBUTTONDOWN) {
        if (e.button.button == 1) {
            retE.type = EVENT_MOUSE_LEFT_DOWN;
        }
        retE.leftMouseUp.x = e.button.x;
        retE.leftMouseUp.y = e.button.y;
    } else if (e.type == SDL_KEYDOWN) {
        retE.type = EVENT_KEY_DOWN;
        retE.keyboardDown.key = e.key.keysym.sym;
    } else if (e.type == SDL_KEYUP) {
        retE.type = EVENT_KEY_UP;
        retE.keyboardUp.key = e.key.keysym.sym;
    } else {
        retE.type = EVENT_UNKNOWN;
    }
    return retE;
}

RenderBackend *backend_sdl2_create() {
    RenderBackend *sdl2  = (RenderBackend *)mem_alloc(sizeof(RenderBackend));
    sdl2->drawRect = sdl2_backend_default_draw_rect;
    sdl2->fillRect = sdl2_backend_default_fill_rect;
    sdl2->submit = sdl2_backend_default_submit;
    sdl2->clear = sdl2_backend_default_clear;
    sdl2->polling = sdl2_backend_default_polling;
    sdl2->init = sdl2_backend_default_init;
    return sdl2;
}