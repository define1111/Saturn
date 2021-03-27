#ifndef _SENTRY_SATURN_BITSET_TREE_H_
#define _SENTRY_SATURN_BITSET_TREE_H_

#include <data_structures/bitset.h>
#include <data_structures/set.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct tree_node {
    struct tree_node *left, *right, *parent;
} tree_node_t;

typedef struct tree
{
    tree_node_t *root;
    unsigned int one_n;
    unsigned int depth;
} tree_t;

typedef struct tree_iterator {
    bitset_t bitset;
    unsigned int depth;
    tree_t *tree;
    tree_node_t *node;
} tree_iterator_t;

typedef struct stack_info {
    int k, level;
    tree_node_t *node;
} stack_info_t;

tree_t init_bitset_tree(int k, int n);
tree_t init_bitset_tree_iteratively(int k, int n);
void print_bitset_tree(const tree_t *tree);
void print_bitset_tree_word(const tree_t *tree);
void free_bitset_tree(tree_t *tree);
tree_iterator_t init_bitset_tree_iterator(tree_t *tree);
set_t *get_nums_by_iterator(const tree_iterator_t *it, T offset);
set_t *get_nums_by_iterator_with_offset(const tree_iterator_t *it);
void next_iterator_pos(tree_iterator_t *it);
void free_bitset_tree_iterator(tree_iterator_t *iter);

#endif