#ifndef __UI_WEB_HTML_PARSER_H__
#define __UI_WEB_HTML_PARSER_H__

#include "../dlist.h"
#include "../trie_tree.h"

typedef unsigned char bool;
#define true 1
#define false 0 

#define INIT_DNODE(node) {  \
    do {    \
        node.left = NULL;  \
        node.right = NULL; \
    } while(0); \
}

typedef struct HtmlAttribute {
    char *key;
    char *val;

    DListNode node;
} HtmlAttribute;

typedef enum HtmlElementType {
    HTML_ELEMENT_TYPE_DOM,
    HTML_ELEMENT_TYPE_CONTENT
} HtmlElementType;

typedef struct HtmlDomElement {
    char *tag;
    char *id;
    char *name;

    DListNode node;

    TrieTreeNode idNode;
    TrieTreeNode nameNode;

    HtmlAttribute *attributes;

    struct HtmlElement *childrens;
} HtmlDomElement;

typedef struct HtmlContentElement {
    DListNode node;
    char *content;
} HtmlContentElement;

typedef struct HtmlElement {
    HtmlElementType type;
    struct HtmlElement *parent;
    union {
        HtmlDomElement dom;
        HtmlContentElement content;
    };
} HtmlElement;

typedef struct HtmlElement* (*HtmlDocumentGetElementById)(struct HtmlDocument *, char *);
typedef struct HtmlElement* (*HtmlDocumentGetElementByName)(struct HtmlDocument *, char *);
typedef void (*HtmlDocumentDump)(struct HtmlDocument *);

typedef struct HtmlDocument {
    HtmlElement *body;

    TrieTreeNode *idTree;
    TrieTreeNode *nameTree;

    HtmlDocumentGetElementById get_element_by_id;
    HtmlDocumentGetElementByName get_element_by_name;
    HtmlDocumentDump dump;
} HtmlDocument;

char* document_consume_whitespace(char *doc);
char *document_match_and_consume(char *doc, char *tok);
char *document_parse_str(char *doc, char *bound);
char *document_parse_tag(char *doc);
char *document_parse_childrens(HtmlElement *children, char *doc);
char *document_parse_attributes(HtmlAttribute* attr, char *doc);
void document_dump(HtmlDocument *document);
struct HtmlDocument *document_load(const char *doc);

#endif /* __UI_WEB_HTML_PARSER_H__ */