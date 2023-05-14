#include <stdio.h>
#include "../include/assert.h"
#include "../include/web/html_document.h"

DEFINE_TEST_CASE(document_should_not_be_null) {
    struct HtmlDocument* document = document_load("<body id=\"test\">sss</body>");
    ASSERT_NOT_NULL(document);
}

DEFINE_TEST_CASE(element_id_should_equal) {
    struct HtmlDocument* document = document_load("<body id=\"test\">sss</body>");
    struct HtmlElement* element = document->get_element_by_id(document, "test");
    ASSERT_NOT_NULL(element);
    ASSERT_STR_EQUAL(element->id, "test");
}

int main(int argc, char* argv[]) {
    // RUN_ALL_TESTS();
    TEST_document_should_not_be_null();
    TEST_element_id_should_equal();
    return 0;
}