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
        "<button onclick=\"button1_click\" width=\"400\" height=\"80\" x=\"0\" y=\"0\" background=\"rgb(50,45,41)\">text</button>"

        "<button onclick=\"button1_click\" width=\"100\" height=\"60\" x=\"0\" y=\"80\" background=\"rgb(67,62,59)\">text</button>"
        "<button onclick=\"button2_click\" width=\"100\" height=\"60\" x=\"100\" y=\"80\" background=\"rgb(67,62,59)\">text</button>"
        "<button onclick=\"button3_click\" width=\"100\" height=\"60\" x=\"200\" y=\"80\" background=\"rgb(67,62,59)\">text</button>"
        "<button width=\"100\" height=\"60\" x=\"300\" y=\"80\" background=\"rgb(242,163,60)\">text</button>"

        "<button width=\"100\" height=\"60\" x=\"0\" y=\"140\" background=\"rgb(105,101,98)\">text</button>"
        "<button width=\"100\" height=\"60\" x=\"100\" y=\"140\" background=\"rgb(105,101,98)\">text</button>"
        "<button width=\"100\" height=\"60\" x=\"200\" y=\"140\" background=\"rgb(105,101,98)\">text</button>"
        "<button width=\"100\" height=\"60\" x=\"300\" y=\"140\" background=\"rgb(242,163,60)\">text</button>"

        "<button width=\"100\" height=\"60\" x=\"0\" y=\"200\" background=\"rgb(105,101,98)\">text</button>"
        "<button width=\"100\" height=\"60\" x=\"100\" y=\"200\" background=\"rgb(105,101,98)\">text</button>"
        "<button width=\"100\" height=\"60\" x=\"200\" y=\"200\" background=\"rgb(105,101,98)\">text</button>"
        "<button width=\"100\" height=\"60\" x=\"300\" y=\"200\" background=\"rgb(242,163,60)\">text</button>"

        "<button width=\"100\" height=\"60\" x=\"0\" y=\"260\" background=\"rgb(105,101,98)\">text</button>"
        "<button width=\"100\" height=\"60\" x=\"100\" y=\"260\" background=\"rgb(105,101,98)\">text</button>"
        "<button width=\"100\" height=\"60\" x=\"200\" y=\"260\" background=\"rgb(105,101,98)\">text</button>"
        "<button width=\"100\" height=\"60\" x=\"300\" y=\"260\" background=\"rgb(242,163,60)\">text</button>"

        "<button width=\"200\" height=\"60\" x=\"0\" y=\"320\" background=\"rgb(105,101,98)\">text</button>"
        "<button width=\"100\" height=\"60\" x=\"200\" y=\"320\" background=\"rgb(105,101,98)\">text</button>"
        "<button width=\"100\" height=\"60\" x=\"300\" y=\"320\" background=\"rgb(242,163,60)\">text</button>"
    "</body>";
    HtmlDocument* document = document_load(doc);

    // Binding
    document->registerDomFunc(document, "button1_click", button1_click);
    document->registerDomFunc(document, "button2_click", button2_click);
    document->registerDomFunc(document, "button3_click", button3_click);



    document->dump(document);
    printf("\nMem Usage: %d bytes\n", mem_get_usage());

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