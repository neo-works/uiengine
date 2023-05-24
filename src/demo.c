#include <stdio.h>
#include "include/web/html_document.h"

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
    HtmlDocument* document =  document_load(doc);
    document->dump(document);
    return 0;
}