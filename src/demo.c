#include <stdio.h>
#include "include/web/html_document.h"

int main(int argc, char* argv[]) {
    char *doc = "<body id=\"test_id\"><p background=\"rgb(10,20,30)\">text</p><button width=\"20px\" onclick=\"hello\">click</button></body>";
    HtmlDocument* document =  document_load(doc);
    document->dump(document);
    return 0;
}