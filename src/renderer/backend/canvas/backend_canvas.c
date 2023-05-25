#include "../../../../include/renderer/renderer.h"
#include "../../../../include/mem/mem.h"

void canvas_backend_default_draw_rect(RenderBackend *canvas, Position pos, Size size, Color backgroundColor) {
    for (uint32_t y = pos.y; y < (pos.y + size.height); y++) {
        for (uint32_t x = pos.x; x < (pos.x + size.width); x++) {
            /* TODO */
        }
    }
}

RenderBackend *backend_canvas_create() {
    RenderBackend *canvas  = (RenderBackend *)mem_alloc(sizeof(RenderBackend));
    canvas->drawRect = backend_canvas_create;
}