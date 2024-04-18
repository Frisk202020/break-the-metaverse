#ifndef MAIN
#define MAIN

#include <stdbool.h>

typedef struct tree_root tree_root;
typedef tree_root* tree;
struct tree_root {
    char* filename;
    tree* contents;
    int size;
};

tree nil();
bool is_empty(tree tr);
tree* create_root(int size);
void print_tree(tree tr, int size, int depth);
void free_tree(tree tr, int n);

#endif