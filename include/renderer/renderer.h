#ifndef __UIENGINE_RENDERER_RENDERER_H__
#define __UIENGINE_RENDERER_RENDERER_H__

#include <stdint.h>
#include <stddef.h>

typedef struct Position {
    uint32_t x;
    uint32_t y;
} Position;

typedef struct Size {
    uint32_t width;
    uint32_t height;
} Size;

typedef struct Padding {
    uint32_t left;
    uint32_t right;
    uint32_t top;
    uint32_t bottom;
} Padding;

typedef struct Margin {
    uint32_t left;
    uint32_t right;
    uint32_t top;
    uint32_t bottom;
} Margin;

typedef struct Color {
    uint8_t a;
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Color;

typedef void (*RenderBackendDrawRect)(struct RenderBackend *, Position, Size, Color);
typedef struct RenderBackend {
    RenderBackendDrawRect drawRect;
} RenderBackend;

typedef void (*RendererDrawRect)(struct Renderer *, Position, Size, Color);
typedef struct Renderer {
    RenderBackend *renderBackend;

    RendererDrawRect drawRect;
} Renderer;

Renderer *render_create();

#endif /* __UIENGINE_RENDERER_RENDERER_H__ */