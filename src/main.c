#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../include/main.h"
#include "../include/AXelle.h"

tree nil(){
    return NULL;
}

bool is_empty(tree tr){
    if (tr == nil()){
        return true;
    }
    return false;
}

tree* create_root(int size){
    tree* root = (tree*)malloc(size*sizeof(tree));
    for (int i = 0; i < size; i++){
        root[i] = malloc(sizeof(tree_root));
    }
    return root;
}

void tabulations(int depth){
    for (int i = 0; i < depth; i++){
        printf("\t");
    }
}

void print_tree(tree tr, int size, int depth){
    if (!is_empty(tr)){
        tabulations(depth);
        printf("%s\n", tr->filename);
        if (tr->contents != NULL){
            for (int i = 0; i < size; i++){
                tree child = tr->contents[i];
                print_tree(child, child->size, depth+1);
            }
            return;
        }
    }
}

void free_tree(tree tr, int size){
    if (tr->contents != NULL){
        for (int i = 0; i < size; i++){
            tree child = tr->contents[i];
            free_tree(child, child->size);
        }
        free(tr->contents);
    }
    free(tr);
}

int main(int argc, char *argv[]){
    if (strcmp(argv[1],"AXelle") == 0){
        AXelle_terminal();
    }

    return 0;
}