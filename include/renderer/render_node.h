#ifndef __UIENGINE_UI_VIEW_H__
#define __UIENGINE_UI_VIEW_H__

#include <stdint.h>
#include "../dlist.h"
#include "renderer.h"

typedef void (*Render)(struct RenderNode *, struct Renderer *);

typedef struct RenderNode {
    Position pos;
    Size size;
    Padding padding;
    Margin margin;
    Color foregroundColor;
    Color backgroundColor;

    struct RenderNode *children;
    DListNode node;

    Render render;
} RenderNode;

void render_child(RenderNode *renderNode, Renderer *renderer);

#endif /* __UIENGINE_UI_VIEW_H__ */