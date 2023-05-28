#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "include/mem/mem.h"
#include "include/web/html_document.h"
#include "include/renderer/renderer.h"
#include "include/renderer/component/button.h"
#include "src/renderer/backend/sdl2/backend_sdl2.h"

int main(int argc, char* argv[]) {
    char *doc = "<body id=\"test_id\">"
                    "<button width=\"100\" height=\"60\" x=\"10\" y=\"10\" background=\"rgb(10,20,30)\">text</button>"
                    "<button width=\"100\" height=\"60\" x=\"120\" y=\"10\" background=\"rgb(10,20,30)\">text</button>"
                    "<button width=\"100\" height=\"60\" x=\"230\" y=\"10\" background=\"rgb(10,20,30)\">text</button>"
                    "<button width=\"100\" height=\"60\" x=\"340\" y=\"10\" background=\"rgb(10,20,30)\">text</button>"
                    "<button width=\"100\" height=\"60\" x=\"450\" y=\"10\" background=\"rgb(10,20,30)\">text</button>"

                    "<button width=\"100\" height=\"60\" x=\"10\" y=\"100\" background=\"rgb(10,20,30)\">text</button>"
                    "<button width=\"100\" height=\"60\" x=\"120\" y=\"100\" background=\"rgb(10,20,30)\">text</button>"
                    "<button width=\"100\" height=\"60\" x=\"230\" y=\"100\" background=\"rgb(10,20,30)\">text</button>"
                    "<button width=\"100\" height=\"60\" x=\"340\" y=\"100\" background=\"rgb(10,20,30)\">text</button>"
                    "<button width=\"100\" height=\"60\" x=\"450\" y=\"100\" background=\"rgb(10,20,30)\">text</button>"

                    "<button width=\"100\" height=\"60\" x=\"10\" y=\"200\" background=\"rgb(10,20,30)\">text</button>"
                    "<button width=\"100\" height=\"60\" x=\"120\" y=\"200\" background=\"rgb(10,20,30)\">text</button>"
                    "<button width=\"100\" height=\"60\" x=\"230\" y=\"200\" background=\"rgb(10,20,30)\">text</button>"
                    "<button width=\"100\" height=\"60\" x=\"340\" y=\"200\" background=\"rgb(10,20,30)\">text</button>"
                    "<button width=\"100\" height=\"60\" x=\"450\" y=\"200\" background=\"rgb(10,20,30)\">text</button>"

                    "<div width=\"100\" height=\"60\" x=\"450\" y=\"200\" background=\"rgb(10,20,30)\">text</div>"
                "</body>";
    HtmlDocument* document = document_load(doc);
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