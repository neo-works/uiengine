#ifndef __UI_WEB_HTML_PARSER_H__
#define __UI_WEB_HTML_PARSER_H__

#include "../dlist.h"
#include "../trie_tree.h"

typedef struct HtmlElement {
    char *id;
    char *name;
    DListNode node;

    TrieTreeNode idNode;
    TrieTreeNode nameNode;

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

struct HtmlDocument *document_load(const char *doc);

#endif /* __UI_WEB_HTML_PARSER_H__ */