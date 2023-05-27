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
                    "<p background=\"rgb(10,20,30)\">text</p>"
                    "<button width=\"20px\" onclick=\"hello\">click</button>"
                    "<div height=\"3em\">"
                        "<h1>welcome to neo ui 1</h1>"
                        "<h2>welcome to neo ui 2</h2>"
                        "<h3>welcome to neo ui 3</h3>"
                        "<h4>welcome to neo ui 4</h4>"
                        "sss"
                        "<ul>"
                            "<li>·li 1</li>"
                            "<li>·li 2</li>"
                            "<li>·li 3</li>"
                        "</ul>"
                        "{{ EXPR }}"
                        "<a href=\"www.baidu.com\">go</a>"
                    "</div>"
                "</body>";
    HtmlDocument* document = document_load(doc);
    document->dump(document);
    printf("\nMem Usage: %d bytes\n", mem_get_usage());

    RenderNode *rootNode = (RenderNode*)mem_alloc(sizeof(RenderNode));

    Button *button = button_create();
    button->renderNode.pos.x = 10;
    button->renderNode.pos.y = 10;
    button->renderNode.size.width = 20;
    button->renderNode.size.height = 10;
    button->renderNode.backgroundColor.r = 255;
    button->renderNode.backgroundColor.g = 0;
    button->renderNode.backgroundColor.b = 0;
    button->renderNode.backgroundColor.a = 0;

    rootNode->children = &button->renderNode;

    Renderer *renderer = render_create();
    RenderBackend* sdl2 = backend_sdl2_create();
    renderer->registerBackend(renderer, sdl2);
    renderer->setRootRenderNode(renderer, rootNode);
    renderer->init(renderer);

    while (renderer->runningState != RENDERER_STATE_STOP) {
        renderer->processEvent(renderer);
        renderer->render(renderer);
    }
    renderer->destroy(renderer);

    return 0;
}