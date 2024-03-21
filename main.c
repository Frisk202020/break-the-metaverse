#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/main.h"

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
    tree home = (tree)malloc(sizeof(tree_root));
    home->filename = "Home";
    tree* root = create_root(3);
    root[0]->filename = "data";
    root[1]->filename = "bin";
    root[2]->filename = "doc";
    home->contents = root;
    home->size = 3;
    
    tree data = root[0];
    tree* dataC = create_root(2);
    dataC[0]->filename = "file 1";
    dataC[1]->filename = "file 2";
    data->contents = dataC;
    data->size = 2;

    tree bin = root[1];
    bin->contents = NULL;
    bin->size = 0;

    tree doc = root[2];
    doc->contents = NULL;
    doc->size = 0;

    tree file1 = dataC[0];
    file1->contents = NULL;
    file1->size = 0;

    tree file2 = dataC[1];
    file2->contents = NULL;
    file2->size = 0;

    print_tree(home, 3, 0);
    free_tree(home, 3);

    return 0;
}