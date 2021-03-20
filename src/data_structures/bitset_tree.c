#include <data_structures/bitset_tree.h>

static tree_node_t *
create_node(int k, int level, int n, tree_node_t *parent)
{
    int free_n = n - level;
    if (k > free_n)
        return NULL;
    tree_node_t *node = malloc(sizeof(tree_node_t));
    node->parent = parent;
    if (k == 0 && level <= n)
    {
        node->left = NULL;
        node->right = create_node(0, level + 1, n, node);
    }
    else
    {
        node->left = create_node(k - 1, level + 1, n, node);
        node->right = create_node(k, level + 1, n, node);
    }
    return node;
}

/// Initialize tree of bitsets consisting of `k` ones at `n` positions.
tree_t
init_bitset_tree(int k, int n)
{
    tree_t tree;
    tree.root = create_node(k, 0, n, NULL);
    tree.leaves_n = 0;
    tree.depth = n;
    return tree;
}

static void
print_bitset_tree_node(tree_node_t *node, bitset_t *bitset, unsigned int idx)
{
    if (node == NULL)
        return;
    if (node->left != NULL)
    {
        BITSET(bitset->data, idx);
        print_bitset_tree_node(node->left, bitset, idx + 1);
    }
    if (node->right != NULL)
    {
        BITCLEAR(bitset->data, idx);
        print_bitset_tree_node(node->right, bitset, idx + 1);
    }
    if (node->left == NULL && node->right == NULL)
    {
        print_bitset(bitset);
    }
}

void
print_bitset_tree(tree_t *tree)
{
    bitset_t bitset = init_bitset(tree->depth);
    if (tree->root == NULL)
        puts("Tree is empty.");
    else
        print_bitset_tree_node(tree->root, &bitset, 0);
    free_bitset(&bitset);
}

static void
free_tree_node(tree_node_t *node)
{
    if (node == NULL)
        return;
    free_tree_node(node->left);
    free_tree_node(node->right);
    free(node);
}

void
free_bitset_tree(tree_t *tree)
{
    if (tree == NULL)
        return;
    free_tree_node(tree->root);
    tree->root = NULL;
    tree->leaves_n = 0;
    tree->depth = 0;
}