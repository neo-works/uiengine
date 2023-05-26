#ifndef __UIENGINE_RENDERER_TYPE_H__
#define __UIENGINE_RENDERER_TYPE_H__

#include <stdint.h>

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
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} Color;

#endif /* __UIENGINE_RENDERER_TYPE_H__ */