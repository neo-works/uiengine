#include "../../include/ui/button.h"
#include "../../include/mem/mem.h"

void button_default_draw(View *view) {
    Button *button = ContainerOf(view, Button, view);
}

Button *button_create() {
    Button *button = (Button *)mem_alloc(sizeof(Button));
    button->view.draw = button_default_draw;
    return button;
}