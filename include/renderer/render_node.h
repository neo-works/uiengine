#ifndef __UIENGINE_UI_VIEW_H__
#define __UIENGINE_UI_VIEW_H__

#include <stdint.h>
#include "../dlist.h"
#include "type.h"
#include "renderer.h"

typedef void (*RenderNodeRender)(struct RenderNode *, struct Renderer *);

typedef void (*RenderNodeOnCLick)(struct RenderNode *, Event e);
typedef void (*RenderNodeOnMouseEnter)(struct RenderNode *, Event e);
typedef void (*RenderNodeOnMouseLeave)(struct RenderNode *, Event e);

typedef struct RenderNode {
    Position pos;
    Size size;
    Padding padding;
    Margin margin;
    Color foregroundColor;
    Color backgroundColor;

    struct RenderNode *children;
    DListNode node;
    RenderNodeOnCLick onClick;
    RenderNodeOnMouseEnter onMouseEnter;
    RenderNodeOnMouseLeave onMouseLeave;

    RenderNodeRender render;

    bool mouseIn;
} RenderNode;

void render_child(RenderNode *renderNode, struct Renderer *renderer);

#endif /* __UIENGINE_UI_VIEW_H__ */