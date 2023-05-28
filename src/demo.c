#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "include/mem/mem.h"
#include "include/web/html_document.h"
#include "include/renderer/renderer.h"
#include "include/renderer/component/button.h"
#include "src/renderer/backend/sdl2/backend_sdl2.h"

void button1_click(HtmlElement *elem) {
    if (elem != NULL) {
        printf("button 1 clicked!\n");
    }
}

void button2_click(HtmlElement *elem) {
    if (elem != NULL) {
        printf("button 2 clicked!\n");
    }
}

void button3_click(HtmlElement *elem) {
    if (elem != NULL) {
        printf("button 3 clicked!\n");
    }
}

int main(int argc, char* argv[]) {
    char *doc =
    "<body id=\"test_id\">"
        "<button onclick=\"button1_click\" width=\"100\" height=\"60\" x=\"10\" y=\"10\" background=\"rgb(255,255,255)\">text</button>"
        "<button onclick=\"button2_click\" width=\"100\" height=\"60\" x=\"120\" y=\"10\" background=\"rgb(255,255,255)\">text</button>"
        "<button onclick=\"button3_click\" width=\"100\" height=\"60\" x=\"230\" y=\"10\" background=\"rgb(255,255,255)\">text</button>"
        "<button width=\"100\" height=\"60\" x=\"340\" y=\"10\" background=\"rgb(255,255,255)\">text</button>"
        "<button width=\"100\" height=\"60\" x=\"450\" y=\"10\" background=\"rgb(255,255,255)\">text</button>"

        "<button width=\"100\" height=\"60\" x=\"10\" y=\"100\" background=\"rgb(255,255,255)\">text</button>"
        "<button width=\"100\" height=\"60\" x=\"120\" y=\"100\" background=\"rgb(255,255,255)\">text</button>"
        "<button width=\"100\" height=\"60\" x=\"230\" y=\"100\" background=\"rgb(255,255,255)\">text</button>"
        "<button width=\"100\" height=\"60\" x=\"340\" y=\"100\" background=\"rgb(255,255,255)\">text</button>"
        "<button width=\"100\" height=\"60\" x=\"450\" y=\"100\" background=\"rgb(255,255,255)\">text</button>"

        "<button width=\"100\" height=\"60\" x=\"10\" y=\"190\" background=\"rgb(255,255,255)\">text</button>"
        "<button width=\"100\" height=\"60\" x=\"120\" y=\"190\" background=\"rgb(255,255,255)\">text</button>"
        "<button width=\"100\" height=\"60\" x=\"230\" y=\"190\" background=\"rgb(255,255,255)\">text</button>"
        "<button width=\"100\" height=\"60\" x=\"340\" y=\"190\" background=\"rgb(255,255,255)\">text</button>"
        "<button width=\"100\" height=\"60\" x=\"450\" y=\"190\" background=\"rgb(255,255,255)\">text</button>"
    "</body>";
    HtmlDocument* document = document_load(doc);
    document->dump(document);
    printf("\nMem Usage: %d bytes\n", mem_get_usage());

    // Binding
    document->registerDomFunc(document, "button1_click", button1_click);
    document->registerDomFunc(document, "button2_click", button2_click);
    document->registerDomFunc(document, "button3_click", button3_click);

    Renderer *renderer = render_create();
    RenderBackend* sdl2 = backend_sdl2_create();
    renderer->registerBackend(renderer, sdl2);

    RenderNode *rootNode = document->buildRenderTree(document);
    renderer->setRootRenderNode(renderer, rootNode);

    renderer->dump(renderer);

    renderer->init(renderer);
    while (renderer->runningState != RENDERER_STATE_STOP) {
        renderer->processEvent(renderer);
        document->updateRender(document);
        renderer->render(renderer);
    }
    renderer->destroy(renderer);

    return 0;
}