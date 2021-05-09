#include <stdlib.h>
#include <stdio.h>

#include <data_structures/set.h>

static void
add_item_set_rec(set_t **root, T data, set_t *parent)
{
    if (*root == NULL)
    {
        set_t *node = malloc(sizeof(set_t));
        node->data = data;
        node->left = NULL;
        node->right = NULL;
        node->parent = parent;
        *root = node;
    }

    if ((*root)->data > data) 
        add_item_set_rec(&(*root)->left, data, *root);
    else if ((*root)->data < data)
        add_item_set_rec(&(*root)->right, data, *root);
}

void add_item_set(set_t **root, T data)
{
    add_item_set_rec(root, data, NULL);
}

void
print_set(const set_t *root)
{
    if (root != NULL)
    {
        print_set(root->left);
        printf("%u ", root->data);
        print_set(root->right);
    }
}

void 
free_set(set_t **root)
{
    if (*root != NULL)
    {
        free_set(&(*root)->left);
        free_set(&(*root)->right);
        free(*root);
    }

    *root = NULL;
}

set_iterator_t
init_set_iterator(set_t *set)
{
    set_iterator_t it;
    if (set == NULL)
    {
        it.node = NULL;
        return it;
    }
    it.node = set;
    while (it.node->left)
        it.node = it.node->left;
    it.prev_node = NULL;
    return it;
}

static void
go_up(set_iterator_t *it)
{
    if (!it->node)
        return;
    do
    {
        it->prev_node = it->node;
        it->node = it->node->parent;
    }
    while (it->node && it->prev_node != it->node->left);
}

void
next_set_iterator_pos(set_iterator_t *it)
{
    if (!it->node)
        return;
    if (!it->node->left && !it->node->right)
    {
        it->prev_node = it->node;
        it->node = it->node->parent;
        if (!it->node)
            return;
        if (it->prev_node == it->node->right)
            go_up(it);
    }
    else
    {
        if (it->prev_node == it->node->left)
        {
            if (it->node->right)
            {
                it->prev_node = it->node;
                it->node = it->node->right;
            }
            else
            {
                go_up(it);
            }
        }
        else if (it->prev_node == it->node->right)
        {
            go_up(it);
        }
        else
        {
            it->prev_node = it->node;
            if (it->node->left)
            {
                it->node = it->node->left;
            }
            else
            {
                it->node = it->node->right;
            }
        }
    }
}