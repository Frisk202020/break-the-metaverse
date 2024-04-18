#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/AXelle.h"
#include "../include/main.h"

void AXelle_terminal(){
    tree home = (tree)malloc(sizeof(tree_root));
    home->filename = "Home";
    tree* root = create_root(3);
    tree* dataC = create_root(2);
    root[0]->filename = "data";
    root[1]->filename = "bin";
    root[2]->filename = "doc";
    home->contents = root;
    home->size = 3;

    tree data = root[0];
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
}