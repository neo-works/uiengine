#include "../../../include/renderer/component/button.h"
#include "../../../include/mem/mem.h"
#include <stdio.h>

void button_default_render(RenderNode *renderNode, Renderer *renderer) {
    Button *button = ContainerOf(renderNode, Button, renderNode);
    renderer->fillRect(renderer, button->renderNode.pos, button->renderNode.size, button->renderNode.backgroundColor);
    renderer->drawRect(renderer, button->renderNode.pos, button->renderNode.size, button->renderNode.borderColor);

    render_child(&button->renderNode, renderer);
}

void button_default_onclick(RenderNode *renderNode, Event e) {
    if (renderNode->onCustomClick != NULL) {
        renderNode->onCustomClick(renderNode, renderNode->dom);
    }
}

void button_default_onmouse_enter(RenderNode *renderNode, Event e) {
    if (renderNode->onCustomMouseEnter != NULL) {
        renderNode->onCustomMouseEnter(renderNode, renderNode->dom);
    }
    if (renderNode->onCustomMouseHover != NULL) {
        renderNode->onCustomMouseHover(renderNode, renderNode->dom);
    }
}

void button_default_onmouse_leave(RenderNode *renderNode, Event e) {
    if (renderNode->onCustomMouseLeave != NULL) {
        renderNode->onCustomMouseLeave(renderNode, renderNode->dom);
    }
}

void button_default_onmouse_hover(RenderNode *renderNode, Event e) {
    if (renderNode->onCustomMouseHover != NULL) {
        renderNode->onCustomMouseHover(renderNode, renderNode->dom);
    }
}

Button *button_create() {
    Button *button = (Button *)mem_alloc(sizeof(Button));
    button->renderNode.render = button_default_render;
    button->renderNode.onClick = button_default_onclick;
    button->renderNode.onCustomClick = NULL;
    button->renderNode.onMouseEnter = button_default_onmouse_enter;
    button->renderNode.onCustomMouseEnter = NULL;
    button->renderNode.onMouseLeave = button_default_onmouse_leave;
    button->renderNode.onCustomMouseLeave = NULL;
    button->renderNode.onMouseHover = button_default_onmouse_hover;
    button->renderNode.onCustomMouseHover = NULL;
    return button;
}