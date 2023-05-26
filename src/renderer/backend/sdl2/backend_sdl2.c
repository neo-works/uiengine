#include "../../../../include/renderer/renderer.h"
#include "../../../../include/mem/mem.h"
#include <stdio.h>

void sdl2_backend_default_draw_rect(RenderBackend *sdl2, Position pos, Size size, Color backgroundColor) {
    for (uint32_t y = pos.y; y < (pos.y + size.height); y++) {
        for (uint32_t x = pos.x; x < (pos.x + size.width); x++) {
            /* TODO */
        }
    }
}

void sdl2_backend_default_init(struct RenderBackend *sdl2) {
    printf("sdl2: init\n");
    return;
}

RenderBackend *backend_sdl2_create() {
    RenderBackend *sdl2  = (RenderBackend *)mem_alloc(sizeof(RenderBackend));
    sdl2->drawRect = sdl2_backend_default_draw_rect;
    sdl2->init = sdl2_backend_default_init;
    return sdl2;
}