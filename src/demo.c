#include <stdio.h>
#include "../include/assert.h"
#include "../include/web/html_document.h"

int main(int argc, char* argv[]) {
    struct HtmlDocument* document = document_load("<body id=\"test\">sss</body>");
    ASSERT_NOT_NULL(document);

    struct HtmlElement* element = document->get_element_by_id("test");

    ASSERT_NOT_NULL(element);
    ASSERT_STR_EQUAL(element->id, "test");

    return 0;
}