#include "../../../include/renderer/component/button.h"
#include "../../../include/mem/mem.h"

void button_default_render(RenderNode *renderNode, Renderer *renderer) {
    Button *button = ContainerOf(renderNode, Button, renderNode);
    renderer->drawRect(renderer, button->renderNode.pos, button->renderNode.size, button->renderNode.backgroundColor);

    render_child(&button->renderNode, renderer);
}

Button *button_create() {
    Button *button = (Button *)mem_alloc(sizeof(Button));
    button->renderNode.render = button_default_render;
    return button;
}