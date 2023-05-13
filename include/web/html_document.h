#ifndef __UI_WEB_HTML_PARSER_H__
#define __UI_WEB_HTML_PARSER_H__

typedef struct HtmlElement {
    char *id;
    char *name;
} HtmlElement;

typedef struct HtmlElement* (*HtmlDocumentGetElementById)(char *);
typedef struct HtmlElement* (*HtmlDocumentGetElementByName)(char *);

typedef struct HtmlDocument {
    HtmlDocumentGetElementById get_element_by_id;
    HtmlDocumentGetElementByName get_element_by_name;
} HtmlDocument;

struct HtmlDocument *document_load(const char *doc);

#endif /* __UI_WEB_HTML_PARSER_H__ */