#include <stdio.h>
#include <stdlib.h>

#include "../../include/Saturn/algebraic_structures/numerical_group_ring_cyclic_group_8bit.h"

int
test_add_null(unsigned int group_order, unsigned int ring_order)
{
    n_gr_ccl_8b_t gr = init_n_gr_ccl_8b(group_order, ring_order);
    unsigned char *result = malloc(gr.group_ring_order * sizeof(unsigned char));

    for (unsigned int i = 0; i < gr.group_ring_order; ++i)
    {
        add_elements_n_gr_ccl_8b(&gr, 0, i, result);
        unsigned int index = result_to_index_n_gr_ccl_8b(&gr, result);
        if (index != i)
        {
            free_n_gr_ccl_8b(&gr);
            free(result);
            return 0;
        }
    }

    for (unsigned int i = 0; i < gr.group_ring_order; ++i)
    {
        add_elements_n_gr_ccl_8b(&gr, i, 0, result);
        unsigned int index = result_to_index_n_gr_ccl_8b(&gr, result);
        if (index != i)
        {
            free_n_gr_ccl_8b(&gr);
            free(result);
            return 0;
        }
    }

    free_n_gr_ccl_8b(&gr);
    free(result);

    return 1;
}

int
main()
{
    int bool1 = test_add_null(5, 5);

    printf("test_add_null: %d\n", bool1);

    return 0;
}