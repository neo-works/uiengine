#include <stdio.h>
#include "include/mem/mem.h"
#include "include/web/html_document.h"
#include "include/renderer/renderer.h"
#include "include/renderer/component/button.h"
#include "src/renderer/backend/canvas/backend_canvas.h"

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
                        "ttt"
                        "<a href=\"www.baidu.com\">go</a>"
                    "</div>"
                "</body>";
    HtmlDocument* document = document_load(doc);
    document->dump(document);
    printf("\nMem Usage: %d bytes\n", mem_get_usage());

    Button *button = button_create();
    Renderer *renderer = render_create();
    RenderBackend* canvas = backend_canvas_create();
    renderer->registerBackend(renderer, canvas);
    renderer->setRootRenderNode(renderer, &button->renderNode);
    renderer->render(renderer);

    return 0;
}