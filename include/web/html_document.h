#ifndef __UI_WEB_HTML_PARSER_H__
#define __UI_WEB_HTML_PARSER_H__

#include "../dlist.h"
#include "../trie_tree.h"

typedef struct HtmlAttribute {
    char *key;
    char *val;

    DListNode node;
} HtmlAttribute;

typedef struct HtmlElement {
    char *tag;
    char *id;
    char *name;
    char *content;

    DListNode node;

    TrieTreeNode idNode;
    TrieTreeNode nameNode;

    HtmlAttribute *attributes;

    struct HtmlElement *childrens;
} HtmlElement;

typedef struct HtmlElement* (*HtmlDocumentGetElementById)(struct HtmlDocument *, char *);
typedef struct HtmlElement* (*HtmlDocumentGetElementByName)(struct HtmlDocument *, char *);

typedef struct HtmlDocument {
    HtmlElement *body;

    TrieTreeNode *idTree;
    TrieTreeNode *nameTree;

    HtmlDocumentGetElementById get_element_by_id;
    HtmlDocumentGetElementByName get_element_by_name;
} HtmlDocument;


char* document_consume_whitespace(char *doc);
char *document_match_and_consume(char *doc, char *tok);
char *document_parse_str(char *doc);
char *document_parse_tag(char *doc);
HtmlElement *document_parse_childrens(char *doc);
HtmlAttribute *document_parse_attributes(char *doc);
struct HtmlDocument *document_load(const char *doc);

#endif /* __UI_WEB_HTML_PARSER_H__ */