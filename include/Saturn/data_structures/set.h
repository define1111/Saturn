#ifndef _SENTRY_SATURN_SET_H_
#define _SENTRY_SATURN_SET_H_

typedef unsigned int T;

struct set_tag
{
    T data;
    struct set_tag *parent;
    struct set_tag *left;
    struct set_tag *right;
};

typedef struct set_tag set_t;

typedef struct set_iterator
{
    struct set_tag *prev_node, *node;
} set_iterator_t;

void add_item_set(set_t **root, T value);
int contains(const set_t *set, T value);
void print_set(const set_t *set);
void free_set(set_t **set);
set_iterator_t init_set_iterator(set_t *set);
void next_set_iterator_pos(set_iterator_t *it);

#endif