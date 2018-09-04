#include <stdio.h>
#include <stdlib.h>
#include "btree.h"
#include "array.h"

void BTreeSplitChild (BTreeNode* target, int insertAt){

    BTreeNode* right = BTreeNode__new(); // z
    BTreeNode* left = target->children[insertAt];

    right->leaf = left->leaf;

    right->n = T - 1;
    for(int j = 0; j < right->n ; j++){
        right->keys[j] = left->keys[j+T];
    }

    if(!left->leaf){
        for(int j = 0; j < T; j++){
            right->children[j] = left->children[j+T];
        }
    }

    left->n = T - 1;

    for(int j = (target->n - 1); j > insertAt + 1; j--){
        target->children[j+1] = target->children[j];
    }

    target->children[insertAt+1] = right;

    for(int j = target->n; j > insertAt; j-- ){
        target->keys[j] = target->keys[j-1];
    }

    target->keys[insertAt] = left->keys[T-1];
    target->n++;

}

void BTreeInsertNonfull (BTreeNode* x, int k){

    if(x->leaf){
        x->keys[x->n] = k;
        x->n++;
        insertionSort(x->keys, x->n);
    }else{
        int i = x->n;

        while(i > 0 && k < x->keys[i-1] ){
            i--;
        }

        if( x->children[i]->n == ((2 * T) - 1) ){
            BTreeSplitChild(x, i);
            if(k > x->keys[i]){
                i = i + 1;
            }
        }
        BTreeInsertNonfull(x->children[i], k);
    }
}

void BTreeNode__show(BTreeNode* x){
    printf("{");

    if(x){
        printf("\"leaf\": %d, ", x->leaf);
        printf("\"n\": %d ,", x->n);
        printf("\"keys\": ");
        printArray(x->keys, x->n);
        printf(" ,\"children\": [");

        if(!x->leaf){
            int i;

            for(i = 0; i < x->n; i++){
                BTreeNode__show(x->children[i]);
            }

            BTreeNode__show(x->children[i]);

        }

        printf("]");

    }

    printf(" }, ");
}
void show(BTree* self){
    BTreeNode__show(self->root);
}

void add(BTree* self, int k){

    BTreeNode* r = self->root;

    if (r->n == ((2 * T) - 1)){
        BTreeNode* s = BTreeNode__new();

        self->root = s;
        s->leaf = FALSE;
        s->n = 0;
        s->children[0] = r;

        BTreeSplitChild(s, 0);
        BTreeInsertNonfull(s, k);
    } else {
        BTreeInsertNonfull(r, k);
    }

}

BTree BTree__new(){
    BTree bTree;
    bTree.root = BTreeNode__new();
    bTree.add = &add;
    bTree.show = &show;
    return bTree;
};
