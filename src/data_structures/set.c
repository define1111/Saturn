#include <stdlib.h>
#include <stdio.h>

#include "../../include/Saturn/data_structures/set.h"

set_t *
init_set()
{
    set_t *set = malloc(sizeof(set_t));

    set->size = 0;
    set->capacity = CAPACITY_STEP;
    set->data = malloc(set->capacity * sizeof(T));

    return set;
}

void 
add_item_set(set_t *set, T value)
{
    for (int i = 0; i < set->size; ++i)
        if (set->data[i] == value)
            return;

    if (set->size >= set->capacity)
    {
        set->capacity += CAPACITY_STEP;
        set->data = realloc(set->data, set->capacity * sizeof(T));
    }

    set->data[set->size] = value;
    set->size += 1;
}

void
print_set(set_t* set)
{
    for (int i = 0; i < set->size; ++i)
        printf("%d ", set->data[i]);
    printf("\n");
}

void 
free_set(set_t **set)
{
    free((*set)->data);
    free(*set);
    *set = NULL;
}
