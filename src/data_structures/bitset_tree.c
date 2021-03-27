#include <data_structures/bitset_tree.h>
#include <data_structures/stack.h>
#include <assert.h>

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
    tree.one_n = k;
    tree.depth = n;
    return tree;
}

tree_t
init_bitset_tree_iteratively(int k, int n)
{
    tree_t tree;
    tree.one_n = k;
    tree.depth = n;
    if (n < 1) {
        tree.root = NULL;
        return tree;
    }
    tree.root = malloc(sizeof(tree_node_t));
    tree.root->parent = NULL;
    stack_info_t info;
    info.k = k;
    info.level = 0;
    info.node = tree.root;
    stack_t stack = init_stack();
    push(&stack, info);
    int total = 1;
    while (!is_empty(stack)) {
        stack_info_t node_info = pop(&stack);
        
        stack_info_t left_info;
        left_info.k = node_info.k - 1;
        left_info.level = node_info.level + 1;
        int free_on_next_left_level = n - left_info.level;
        if (left_info.k > free_on_next_left_level || node_info.k == 0) {
            node_info.node->left = NULL;
        } else {
            left_info.node = malloc(sizeof(tree_node_t));
            push(&stack, left_info);
            node_info.node->left = left_info.node;
            left_info.node->parent = node_info.node;
            total += 1;
        }

        stack_info_t right_info;
        right_info.k = node_info.k;
        right_info.level = node_info.level + 1;
        int free_on_next_right_level = n - right_info.level;
        if (right_info.k > free_on_next_right_level || node_info.k == 0) {
            node_info.node->right = NULL;
        } else {
            right_info.node = malloc(sizeof(tree_node_t));
            push(&stack, right_info);
            node_info.node->right = right_info.node;
            right_info.node->parent = node_info.node;
            total += 1;
        }
    }
    printf("Total node count: %d\n", total);
    return tree;
}

static void
print_bitset_tree_node(const tree_node_t *node, const bitset_t *bitset, unsigned int idx)
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
print_bitset_tree(const tree_t *tree)
{
    bitset_t bitset = init_bitset(tree->depth);
    if (tree->root == NULL)
        puts("Tree is empty.");
    else
        print_bitset_tree_node(tree->root, &bitset, 0);
    free_bitset(&bitset);
}

static void
print_bitset_tree_word_rec(const tree_node_t *node, char letter)
{
    printf("%c", letter);
    if (node->left)
        print_bitset_tree_word_rec(node->left, 'L');
    if (node->right)
        print_bitset_tree_word_rec(node->right, 'R');
    printf("%c", 'U');
}

void
print_bitset_tree_word(const tree_t *tree)
{
    if (tree->root)
    {
        print_bitset_tree_word_rec(tree->root, 'B');
    }
    printf("E\n");
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
    tree->one_n = 0;
    tree->depth = 0;
}

tree_iterator_t
init_bitset_tree_iterator(tree_t *tree)
{
    tree_iterator_t it;
    it.bitset = init_bitset(tree->depth);
    it.tree = tree;
    it.node = NULL;
    tree_node_t *first_leaf = tree->root;
    it.depth = 0;
    while (first_leaf && (first_leaf->left || first_leaf->right)){
        assert(it.depth <= tree->depth &&
            "Invalid depth on tree initialization.");
        if (first_leaf->left) {
            BITSET(it.bitset.data, it.depth);
            first_leaf = first_leaf->left;
        } else if (first_leaf->right) {
            first_leaf = first_leaf->right;
        }
        it.depth++;
    }
    it.node = first_leaf;
    //printf("Depth: %u\n", it.depth);
    return it;
}

void
free_bitset_tree_iterator(tree_iterator_t *it)
{
    free_bitset(&it->bitset);
    it->node = NULL;
    it->tree = NULL;
    it->depth = 0;
}

set_t *
get_nums_by_iterator(const tree_iterator_t *it, T offset)
{
    set_t *set = NULL;
    if (!it->tree || !it->node)
        return set;
    for (size_t i = 0; i < it->bitset.length; ++i)
    {
        if (BITTEST(it->bitset.data, i))
        {
            add_item_set(&set, i + offset);
        }
    }
    return set;
}

set_t *
get_nums_by_iterator_with_offset(const tree_iterator_t *it)
{
    set_t *set = get_nums_by_iterator(it, 1);
    add_item_set(&set, 0);
    return set;
}

static void
go_left(tree_iterator_t *it, tree_node_t **last_node, tree_node_t **new_node)
{
    BITSET(it->bitset.data, it->depth);
    it->depth++;
    *last_node = *new_node;
    *new_node = (*new_node)->left;
    //printf("Left, new depth: %u. ", it->depth);
    //print_bitset(&it->bitset);
}

static void
go_right(tree_iterator_t *it, tree_node_t **last_node, tree_node_t **new_node)
{
    BITCLEAR(it->bitset.data, it->depth);
    it->depth++;
    *last_node = *new_node;
    *new_node = (*new_node)->right;
    //printf("Right, new depth: %u. ", it->depth);
    //print_bitset(&it->bitset);
}

static void
go_up(tree_iterator_t *it, tree_node_t **last_node, tree_node_t **new_node)
{
    if ((*new_node)->parent) {
        assert(it->depth > 0 && "Leaf depth must be positive.");
        it->depth--;
        BITCLEAR(it->bitset.data, it->depth);
    }
    *last_node = *new_node;
    *new_node = (*new_node)->parent;
    //printf("Up, new depth: %u. ", it->depth);
    //print_bitset(&it->bitset);
}

void
next_iterator_pos(tree_iterator_t *it)
{
    if (!it->node || it->depth < 1)
    {
        it->node = NULL;
        return;
    }
    it->depth--;
    BITCLEAR(it->bitset.data, it->depth);
    tree_node_t *last_node = it->node;
    tree_node_t *new_node = it->node->parent;
    while (new_node && (new_node->left || new_node->right))
    {
        //printf("Check next node\n");
        if (new_node->left)
        {
            //printf("Has left\n");
            if (new_node->left == last_node)
            {
                if (new_node->right)
                {
                    for (unsigned int i = it->tree->depth - it->depth; i < it->tree->depth; ++i) {
                        BITCLEAR(it->bitset.data, i);
                    }
                    go_right(it, &last_node, &new_node);
                }
                else
                    go_up(it, &last_node, &new_node);
            }
            else if (new_node->parent == last_node)
            {
                go_left(it, &last_node, &new_node);
            }
            else
            {
                go_up(it, &last_node, &new_node);
            }
        }
        else
        {
            //printf("Has right");
            if (new_node->right == last_node)
                go_up(it, &last_node, &new_node);
            else
                go_right(it, &last_node, &new_node);
        }
    }
    it->node = new_node;
}