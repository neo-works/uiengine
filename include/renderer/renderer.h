#ifndef __UIENGINE_RENDERER_RENDERER_H__
#define __UIENGINE_RENDERER_RENDERER_H__

#include <stdint.h>
#include <stddef.h>
#include "type.h"
#include "render_node.h"

typedef void (*RenderBackendDrawRect)(struct RenderBackend *, Position, Size, Color);
typedef void (*RenderBackendInit)(struct RenderBackend *);
typedef struct RenderBackend {
    RenderBackendInit init;
    RenderBackendDrawRect drawRect;
} RenderBackend;

typedef void (*RendererRegisterBackend)(struct Renderer *, RenderBackend *);
typedef void (*RendererSetRootRenderNode)(struct Renderer *, struct RenderNode *);
typedef void (*RendererDrawRect)(struct Renderer *, Position, Size, Color);
typedef void (*RendererRender)(struct Renderer *);
typedef void (*RendererInit)(struct Renderer *);
typedef struct Renderer {
    RenderBackend *renderBackend;
    struct RenderNode *rootNode;

    RendererRegisterBackend registerBackend;
    RendererSetRootRenderNode setRootRenderNode;
    RendererRender render;
    RendererInit init;

    RendererDrawRect drawRect;
} Renderer;

Renderer *render_create();

#endif /* __UIENGINE_RENDERER_RENDERER_H__ */