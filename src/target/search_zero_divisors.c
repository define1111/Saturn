#include <stdio.h>
#include <stdlib.h>

#include <algebraic_structures/numerical_group_ring_cyclic_group_8bit.h>
#include <data_structures/set.h>

/* temp */
#define RING_ORDER (2)
#define GROUP_ORDER (4)

/* temp non-optimizated zero checker */
int
is_zero_result(unsigned char *result, unsigned int size)
{
    for (unsigned int i = 0; i < size; ++i)
        if (result[i] != 0)
            return 0;
    return 1;
}

int
main()
{
    n_gr_ccl_8b_t gr = init_n_gr_ccl_8b(RING_ORDER, GROUP_ORDER);
    set_t *zero_divisors = init_set();
    unsigned char result[GROUP_ORDER];

    for (unsigned int i = 2; i < gr.group_ring_order; ++i)
    {
        for (unsigned int j = i; j < gr.group_ring_order; ++j)
        {
            multy_elements_n_gr_ccl_8b(&gr, i, j, result);
            /* if result is zero then i and j are zero divisors! */
            if (is_zero_result(result, GROUP_ORDER))
            {
                /* temp non-optimizated set */
                add_item_set(zero_divisors, i);
                add_item_set(zero_divisors, j);
            }
        }
    }

    print_n_gr_ccl_8b(&gr);

    free_n_gr_ccl_8b(&gr);

    print_set(zero_divisors);

    free_set(&zero_divisors);

    return 0;
}