#include <stdio.h>
#include "include/web/html_document.h"

int main(int argc, char* argv[]) {
    printf("DocumentDump:\n");
    char *doc = "<body id=\"test_id\">sss</body>";
    HtmlDocument* document =  document_load(doc);
    document->dump(document);
    return 0;
}