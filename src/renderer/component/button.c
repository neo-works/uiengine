#include "../../../include/renderer/component/button.h"
#include "../../../include/mem/mem.h"
#include <stdio.h>

void button_default_render(RenderNode *renderNode, Renderer *renderer) {
    Button *button = ContainerOf(renderNode, Button, renderNode);
    renderer->drawRect(renderer, button->renderNode.pos, button->renderNode.size, button->renderNode.backgroundColor);

    render_child(&button->renderNode, renderer);
}

void button_default_onclick(RenderNode *renderNode, Event e) {
    // TODO: Do some animation
    if (renderNode->onCustomClick != NULL) {
        renderNode->onCustomClick(renderNode, renderNode->dom);
    }
}

void button_default_onmouse_enter(RenderNode *renderNode, Event e) {
    // FIXME: it' just a test
    renderNode->backgroundColor.g = 0;
    renderNode->backgroundColor.b = 0;
}

void button_default_onmouse_leave(RenderNode *renderNode, Event e) {
    // FIXME: it' just a test
    renderNode->backgroundColor.g = 255;
    renderNode->backgroundColor.b = 255;
}

Button *button_create() {
    Button *button = (Button *)mem_alloc(sizeof(Button));
    button->renderNode.render = button_default_render;
    button->renderNode.onClick = button_default_onclick;
    button->renderNode.onCustomClick = NULL;
    button->renderNode.onMouseEnter = button_default_onmouse_enter;
    button->renderNode.onMouseLeave = button_default_onmouse_leave;
    return button;
}