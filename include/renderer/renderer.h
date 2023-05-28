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
    EVENT_EXIT,
    EVENT_MOUSE_MOTION,
    EVENT_MOUSE_LEFT_UP,
    EVENT_MOUSE_LEFT_DOWN,
    EVENT_MOUSE_MIDDLE_UP,
    EVENT_MOUSE_MIDDLE_DOWN,
    EVENT_MOUSE_RIGHT_UP,
    EVENT_MOUSE_RIGHT_DOWN,
    EVENT_KEY_UP,
    EVENT_KEY_DOWN,
    EVENT_UNKNOWN,
} EventType;

typedef struct Event {
    EventType type;
    union {
        struct {
            uint32_t x;
            uint32_t y;
        } mouseMove;
        struct {
            uint32_t x;
            uint32_t y;
        } leftMouseDown;
        struct {
            uint32_t x;
            uint32_t y;
        } leftMouseUp;
         struct {
            uint32_t x;
            uint32_t y;
        } rightMouseDown;
        struct {
            uint32_t x;
            uint32_t y;
        } rightMouseUp;
        struct {
            uint32_t key;
        } keyboardUp;
         struct {
            uint32_t key;
        } keyboardDown;
    };
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
typedef void (*RendererDump)(struct Renderer *);
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

    RendererDump dump;

    RendererDrawRect drawRect;
} Renderer;

Renderer *render_create();

#endif /* __UIENGINE_RENDERER_RENDERER_H__ */