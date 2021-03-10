#ifndef _SENTRY_SATURN_SET_H_
#define _SENTRY_SATURN_SET_H_

typedef int T;

#define CAPACITY_STEP (1024)

typedef struct set_tag
{
    T *data;
    int size;
    int capacity;
} set_t;

set_t *init_set(void);
void add_item_set(set_t *set, T value);
void print_set(set_t *set);
void free_set(set_t **set);

#endif