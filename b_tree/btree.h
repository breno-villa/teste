
#include "btree-node.h"

typedef struct BTree {
    BTreeNode *root;
    void (*add)(struct BTree* self, int key);
    void (*show)(struct BTree* self);
} BTree;

BTree BTree__new();
