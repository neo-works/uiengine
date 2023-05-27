#ifndef __UIENGINE_RENDERER_RENDERER_H__
#define __UIENGINE_RENDERER_RENDERER_H__

#include <stdint.h>
#include <stddef.h>
#include "type.h"
#include "render_node.h"

typedef enum RendererState {
    RENDERER_STATE_RUNNING,
    RENDERER_STATE_STOP,
} RendererState;

typedef enum EventType {
    NO_EVENT,
    EVENT_EXIT,
} EventType;

typedef struct Event {
    EventType type;
} Event;

typedef void (*RenderBackendDrawRect)(struct RenderBackend *, Position, Size, Color);
typedef void (*RenderBackendInit)(struct RenderBackend *);
typedef void (*RenderBackendSubmit)(struct RenderBackend *);
typedef void (*RenderBackendClear)(struct RenderBackend *);
typedef Event (*RenderBackendPolling)(struct RenderBackend *);
typedef struct RenderBackend {
    RenderBackendInit init;
    RenderBackendSubmit submit;
    RenderBackendClear clear;
    RenderBackendPolling polling;
    RenderBackendDrawRect drawRect;
} RenderBackend;

typedef void (*RendererRegisterBackend)(struct Renderer *, RenderBackend *);
typedef void (*RendererSetRootRenderNode)(struct Renderer *, struct RenderNode *);
typedef void (*RendererDrawRect)(struct Renderer *, Position, Size, Color);
typedef void (*RendererRender)(struct Renderer *);
typedef void (*RendererProcessEvent)(struct Renderer *);
typedef void (*RendererInit)(struct Renderer *);
typedef void (*RendererDestroy)(struct Renderer *);
typedef struct Renderer {
    RendererState runningState;

    RenderBackend *renderBackend;
    struct RenderNode *rootNode;

    RendererRegisterBackend registerBackend;
    RendererSetRootRenderNode setRootRenderNode;
    RendererRender render;
    RendererInit init;
    RendererProcessEvent processEvent;
    RendererDestroy destroy;

    RendererDrawRect drawRect;

} Renderer;

Renderer *render_create();

#endif /* __UIENGINE_RENDERER_RENDERER_H__ */