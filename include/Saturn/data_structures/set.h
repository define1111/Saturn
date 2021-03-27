#ifndef _SENTRY_SATURN_SET_H_
#define _SENTRY_SATURN_SET_H_

typedef unsigned int T;

struct set_tag
{
    T data;
    struct set_tag *left;
    struct set_tag *right;
};

typedef struct set_tag set_t;

void add_item_set(set_t **root, T value);
void print_set(const set_t *set);
void free_set(set_t **set);

#endif