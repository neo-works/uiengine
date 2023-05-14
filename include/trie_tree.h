#ifndef __UIENGINE_TRIE_TREE_H__
#define __UIENGINE_TRIE_TREE_H__

typedef struct TrieTreeNode {
    char val;
    struct TrieTreeNode *left;
    struct TrieTreeNode *right;
} TrieTreeNode;

#endif /* __UIENGINE_TRIE_TREE_H__ */