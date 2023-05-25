#ifndef __UIENGINE_UI_VIEW_H__
#define __UIENGINE_UI_VIEW_H__

#include <stdint.h>
#include "../dlist.h"

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

Color ColorARGB(uint8_t a, uint8_t r, uint8_t g, uint8_t b);

Color ColorRGB(uint8_t r, uint8_t g, uint8_t b);

typedef void (*Draw)(struct View *);

typedef struct View {
    Position pos;
    Size size;
    Padding padding;
    Margin margin;
    Color foregroundColor;
    Color backgroundColor;

    struct View *children;
    DListNode node;

    Draw draw;
} View;

#endif /* __UIENGINE_UI_VIEW_H__ */