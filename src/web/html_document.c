#include "../../include/web/html_document.h"
#include "../../include/mem/mem.h"
#include "../../include/assert.h"

HtmlElement* document_default_get_element_by_name(struct HtmlDocument *doc, char *name) {
    return NULL;
}

HtmlElement* document_default_get_element_by_id(struct HtmlDocument *doc, char *id) {
    return NULL;
}

void document_init(HtmlDocument *document) {
    document->get_element_by_id = document_default_get_element_by_id;
    document->get_element_by_name = document_default_get_element_by_name;
}

static iswhitespace(char c) {
    return (c == ' ') || (c == '\t');
}

static isalpha(char c) {
    return ((c >= 'a') && (c <= 'z')) || 
           ((c >= 'A') && (c <= 'Z'));
}

char* document_consume_whitespace(char *doc) {
    while (iswhitespace(*doc)) {
        doc++;
    }
    return doc;
}

char *document_match_and_consume(char *doc, char *tok) {
    char *tok_tmp = tok;
    while ((*doc != '\0') && (*tok_tmp != '\0')) {
        if (*doc == *tok_tmp) {
            doc++;
            tok_tmp++;
        } else {
            break;
        }
    }
    return doc;
}

char *document_parse_str(char *doc) {
    char *tag = mem_alloc(0x20);
    memset(tag, 0, 0x20);
    uint32_t idx = 0;
    while ((*doc != '\0')) {
        if (isalpha(*doc)) {
            tag[idx++] = *doc;
            doc++;
        } else {
            break;
        }
    }
    return tag;
}

char *document_parse_tag(char *doc) {
    return document_parse_str(doc);
}

HtmlElement *document_parse_childrens(char *doc) {
    return NULL;
}

HtmlAttribute *document_parse_attributes(char *doc) {
    return NULL;
}

/**
 * @brief parse element
 * <{TAG} {ATTRIBUTES}>{CHILDRENS}</{TAG}>
 * @param doc 
 * @return HtmlElement* 
 */
HtmlElement *document_parse_element(char *doc) {
    HtmlElement *element = (HtmlDocument *)mem_alloc(sizeof(HtmlDocument));
    doc = document_consume_whitespace(doc);
    doc = document_match_and_consume(doc, "<");
    element->tag = document_parse_tag(doc);
    element->attributes = document_parse_attributes(doc);
    document_match_and_consume(doc, ">");
    element->childrens = document_parse_childrens(doc);
    document_match_and_consume(doc, "</");
    document_match_and_consume(doc, element->tag);
    document_match_and_consume(doc ,">");

    return element;
}

void document_parse(HtmlDocument *document, char *doc) {
    ASSERT_NOT_NULL(document);
    ASSERT_NOT_NULL(doc);
    document->body = document_parse_element(doc);
}

struct HtmlDocument *document_load(const char *doc) {
    HtmlDocument *document = (HtmlDocument*)mem_alloc(sizeof(HtmlDocument));
    document_init(document);
    document_parse(document, doc);
    return document;
}