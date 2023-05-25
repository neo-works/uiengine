#include "../../include/renderer/renderer.h"
#include "../../include/mem/mem.h"

void renderer_default_draw_rect(Renderer *renderer, Position pos, Size size, Color backgroundColor) {
    renderer->renderBackend->drawRect(renderer->renderBackend, pos, size, backgroundColor);
}

Renderer *render_create() {
    Renderer *renderer = (Renderer *)mem_alloc(sizeof(Renderer));
    renderer->drawRect = renderer_default_draw_rect;
    return renderer;
}