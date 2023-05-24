# uiengine
## web
### [html lexer grammer](https://github.com/antlr/grammars-v4/blob/master/html/HTMLLexer.g4)
### [html parser grammer](https://github.com/antlr/grammars-v4/blob/master/html/HTMLParser.g4)
### [css3 grammer](https://github.com/antlr/grammars-v4/blob/master/css3/css3.g4)

## UI & Renderer pipeline
```
vsync  thread:      vsync        vsync                           vsync
ui     thread:      dom1         (event)(update)(frame2)         (event)(update)(frame3)
render thread:                   frame1                          frame2
```