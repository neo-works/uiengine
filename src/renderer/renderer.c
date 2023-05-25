#include "../../include/renderer/renderer.h"
#include "../../include/renderer/render_node.h"
#include "../../include/mem/mem.h"
#include <stdio.h>

void renderer_default_draw_rect(Renderer *renderer, Position pos, Size size, Color backgroundColor) {
    renderer->renderBackend->drawRect(renderer->renderBackend, pos, size, backgroundColor);
}

void renderer_default_register_backend(Renderer *renderer, RenderBackend *renderBackend) {
    renderer->renderBackend = renderBackend;
}

void renderer_default_set_root_render_node(Renderer *renderer, RenderNode *rootNode) {
    renderer->rootNode = rootNode;
}

void renderer_default_render(struct Renderer *renderer) {
    if (renderer->renderBackend == NULL) {
        printf("render should register a backend first!\n");
    }
    render_child(renderer->rootNode, renderer);
}

Renderer *render_create() {
    Renderer *renderer = (Renderer *)mem_alloc(sizeof(Renderer));
    renderer->registerBackend = renderer_default_register_backend;
    renderer->render = renderer_default_render;
    renderer->setRootRenderNode = renderer_default_set_root_render_node;
    renderer->drawRect = renderer_default_draw_rect;
    return renderer;
}