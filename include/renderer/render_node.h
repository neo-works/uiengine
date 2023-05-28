#ifndef __UIENGINE_UI_VIEW_H__
#define __UIENGINE_UI_VIEW_H__

#include <stdint.h>
#include "../dlist.h"
#include "type.h"
#include "renderer.h"
#include "../web/html_document.h"

typedef void (*RenderNodeRender)(struct RenderNode *, struct Renderer *);

typedef void (*RenderNodeOnClick)(struct RenderNode *, Event e);
typedef void (*RenderNodeOnCustomClick)(struct RenderNode *, struct HtmlElement *elem);
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
    RenderNodeOnClick onClick;
    RenderNodeOnCustomClick onCustomClick;
    RenderNodeOnMouseEnter onMouseEnter;
    RenderNodeOnMouseLeave onMouseLeave;

    RenderNodeRender render;
    
    struct HtmlElement *dom;

    bool mouseIn;
} RenderNode;

void render_child(RenderNode *renderNode, struct Renderer *renderer);

#endif /* __UIENGINE_UI_VIEW_H__ */