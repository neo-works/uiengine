#include "../../include/web/html_document.h"
#include "../../include/mem/mem.h"
#include "../../include/assert.h"

HtmlElement* document_default_get_element_by_name(struct HtmlDocument *doc, char *name) {
    return NULL;
}

HtmlElement* document_default_get_element_by_id(struct HtmlDocument *doc, char *id) {
    return NULL;
}

void document_default_dump(struct HtmlDocument *doc) {

}

void document_init(HtmlDocument *document) {
    document->get_element_by_id = document_default_get_element_by_id;
    document->get_element_by_name = document_default_get_element_by_name;
    document->dump = document_default_dump;
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

char* document_match_bound(char *doc) {
    if (*doc == '\"') {
        return "\"";
    } else if (*doc == '\'') {
        return "\'";
    } else {
        perror("syntax error: shoud have a bound\n");
        exit(0);
    }
}

int document_match_str(char *doc, char *str) {
    char *tok_tmp = str;
    while ((*doc != '\0') && (*tok_tmp != '\0')) {
        if (*doc == *tok_tmp) {
            doc++;
            tok_tmp++;
        } else {
            return 0;
        }
    }
    return 1;
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

char *document_parse_str_until(char *doc, char *bound) {
    char *str = mem_alloc(0x20);
    memset(str, 0, 0x20);
    uint32_t idx = 0;
    while ((*doc != '\0') && (*doc != *bound)) {
           str[idx++] = *doc;
           doc++;
    }
    return str;
}

char *document_parse_tag(char *doc) {
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

char *document_parse_childrens(HtmlElement *children, char *doc) {
    char* content = document_parse_str_until(doc, "<");
    INIT_DNODE(children->dom.node);
    children->dom.attributes = NULL;
    children->dom.childrens = NULL;
    children->type = HTML_ELEMENT_TYPE_CONTENT;
    children->content.content = content;
    doc = document_match_and_consume(doc, content);
    return doc;
}

/**
 * @brief parse attribute
 * {KEY}{WHITESPACE}={WHITESPACE}{"/'}{VALUE}{"/'}{WHITESPACE}
 * @param doc 
 * @return HtmlAttribute* 
 */
char *document_parse_attributes(HtmlAttribute* attr, char *doc) {
    HtmlAttribute *head = attr;
    bool first = true;
    while(*doc != '>') {
        if (!first) {
            attr = (HtmlAttribute*)mem_alloc(sizeof(HtmlAttribute));
            INIT_DNODE(attr->node);
        }
        attr->key = document_parse_tag(doc);
        doc = document_match_and_consume(doc, attr->key);
        doc = document_consume_whitespace(doc);
        doc = document_match_and_consume(doc, "=");
        doc = document_consume_whitespace(doc);
        char *bound = document_match_bound(doc);
        doc = document_match_and_consume(doc, bound);
        attr->val = document_parse_str_until(doc, bound);
        doc = document_match_and_consume(doc, attr->val);
        if (strcmp(attr->key, "style") == 0) {
            // TODO: parse css
        }
        doc = document_match_and_consume(doc, bound);
        doc = document_consume_whitespace(doc);

        if (!first) {
            dlist_insert(&head->node, &attr->node);
        }
        first = false;
    }
    attr = head;
    return doc;
}

/**
 * @brief parse element
 * <{TAG}{WHITESPACE}{ATTRIBUTES}{WHITESPACE}>{CHILDRENS}</{TAG}>
 * @param doc 
 * @return HtmlElement* 
 */
HtmlElement *document_parse_element(char *doc) {
    HtmlElement *element = (HtmlElement *)mem_alloc(sizeof(HtmlElement));
    INIT_DNODE(element->dom.node);
    element->dom.attributes = NULL;
    element->dom.childrens = NULL;
    element->parent = NULL;

    doc = document_consume_whitespace(doc);
    doc = document_match_and_consume(doc, "<");
    element->dom.tag = document_parse_tag(doc);
    doc = document_match_and_consume(doc, element->dom.tag);
    doc = document_consume_whitespace(doc);
    if (*doc != '>') {
        HtmlAttribute *attr = (HtmlAttribute*)mem_alloc(sizeof(HtmlAttribute));
        INIT_DNODE(attr->node);
        doc = document_parse_attributes(attr, doc);
        element->dom.attributes = attr;
    }
    doc = document_match_and_consume(doc, ">");
    if (document_match_str(doc, "</")) {
        goto close_tag;
    } else {
        HtmlElement *children = (HtmlElement*)mem_alloc(sizeof(HtmlElement));
        doc = document_parse_childrens(children, doc);
        element->dom.childrens = children;
    }

close_tag:
    doc = document_match_and_consume(doc, "</");
    doc = document_match_and_consume(doc, element->dom.tag);
    doc = document_match_and_consume(doc ,">");
    return element;
}

void document_parse(HtmlDocument *document, char *doc) {
    ASSERT_NOT_NULL(document);
    ASSERT_NOT_NULL(doc);
    document->body = document_parse_element(doc);
}

void document_dump(HtmlDocument *document) {
    return;
}

struct HtmlDocument *document_load(const char *doc) {
    HtmlDocument *document = (HtmlDocument*)mem_alloc(sizeof(HtmlDocument));
    document_init(document);
    document_parse(document, doc);
    return document;
}