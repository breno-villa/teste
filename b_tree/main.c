#include <stdio.h>
#include "btree.h"

int main() {
    BTree bTree = BTree__new();

    for(int i =0; i< 100; i++)
        bTree.add(&bTree, i);

    printf("var bTree = ");
    bTree.show(&bTree);


    return 0;
}
