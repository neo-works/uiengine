#include <stdio.h>
#include "../include/assert.h"
#include "../include/web/html_document.h"

DEFINE_TEST_CASE(element_id_should_equal) {
    struct HtmlDocument* document = document_load("<body id=\"test\">sss</body>");
    struct HtmlElement* element = document->get_element_by_id(document, "test");
    ASSERT_NOT_NULL(element);
    ASSERT_STR_EQUAL(element->id, "test");
    return 0;
}

DEFINE_TEST_CASE(document_should_consume_whitespace) {
    char *doc = "          <body></body>";
    doc = document_consume_whitespace(doc);
    ASSERT_STR_EQUAL(doc, "<body></body>");
    return 0;
}

DEFINE_TEST_CASE(document_should_match_and_consume) {
    char *doc = "<body></body>";
    doc = document_match_and_consume(doc, "<");
    ASSERT_STR_EQUAL(doc, "body></body>");
    doc = document_match_and_consume(doc, "body");
    ASSERT_STR_EQUAL(doc, "></body>");
    doc = document_match_and_consume(doc, ">");
    ASSERT_STR_EQUAL(doc, "</body>");
    doc = document_match_and_consume(doc, "</");
    ASSERT_STR_EQUAL(doc, "body>");
    doc = document_match_and_consume(doc, "body");
    ASSERT_STR_EQUAL(doc, ">");
    doc = document_match_and_consume(doc, ">");
    ASSERT_STR_EQUAL(doc, "\0");
    return 0;
}

DEFINE_TEST_CASE(document_should_parse_tag) {
    char *doc = "body></body>";
    char *tag = document_parse_tag(doc);
    ASSERT_STR_EQUAL(tag, "body");
    return 0;
}

DEFINE_TEST_CASE(document_should_parse_tag_2) {
    char *doc = "<body>sss</body>";
    HtmlDocument *document = document_load(doc);
    ASSERT_NOT_NULL(document);
    ASSERT_NOT_NULL(document->body);
    ASSERT_NOT_NULL(document->body->tag);
    ASSERT_STR_EQUAL(document->body->tag, "body");
    return 0;
}

int main(int argc, char* argv[]) {
    // RUN_ALL_TESTS();
    TEST_document_should_consume_whitespace();
    TEST_document_should_match_and_consume();
    TEST_document_should_parse_tag();
    TEST_document_should_parse_tag_2();
    
    TEST_element_id_should_equal();
    return 0;
}