#include <stdlib.h>
#include <stdio.h>

#include <data_structures/set.h>

void
add_item_set(set_t **root, T data)
{
    if (*root == NULL)
    {
        set_t *node = malloc(sizeof(set_t));
        node->data = data;
        node->left = NULL;
        node->right = NULL;
        *root = node;
    }

    if ((*root)->data > data) 
        add_item_set(&(*root)->left, data);
    else if ((*root)->data < data)
        add_item_set(&(*root)->right, data);
}

void
print_set(set_t *root)
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
