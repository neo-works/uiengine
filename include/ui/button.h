#ifndef __UIENGINE_UI_BUTTON_H__
#define __UIENGINE_UI_BUTTON_H__

#include "view.h"

typedef struct Button {
    View view;
} Button;

Button *button_create();

#endif /* __UIENGINE_UI_BUTTON_H__ */