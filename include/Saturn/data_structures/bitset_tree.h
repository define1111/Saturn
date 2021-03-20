#ifndef _SENTRY_SATURN_BITSET_TREE_H_
#define _SENTRY_SATURN_BITSET_TREE_H_

#include <data_structures/bitset.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct tree_node {
    struct tree_node *left, *right, *parent;
} tree_node_t;

typedef struct tree
{
    tree_node_t *root;
    unsigned int depth;
    unsigned int leaves_n;
} tree_t;

tree_t init_bitset_tree(int k, int n);
void print_bitset_tree(tree_t *tree);
void free_bitset_tree(tree_t *tree);

#endif