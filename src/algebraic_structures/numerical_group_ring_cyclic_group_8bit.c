#include <stdlib.h>
#include <stdio.h>

#include <math.h>

/*#include "../../include/Saturn/algebraic_structures/permutation.h"*/

#include "../../include/Saturn/algebraic_structures/numerical_group_ring_cyclic_group_8bit.h"

/*permutation_t *sigma_arr = NULL;*/

n_gr_ccl_8b_t
init_n_gr_ccl_8b(unsigned char ring_order, unsigned char group_order)
{
    n_gr_ccl_8b_t group_ring;

    group_ring.ring_order = ring_order;
    group_ring.group_order = group_order;
    group_ring.group_ring_order = pow(group_ring.ring_order, group_ring.group_order);

    group_ring.elements = (unsigned char **) malloc(group_ring.group_ring_order * sizeof(unsigned char *));

    for (unsigned int i = 0; i < group_ring.group_ring_order; ++i)
        group_ring.elements[i] = (unsigned char *) malloc(group_ring.group_order * sizeof(unsigned char));

    for (unsigned int j = 0; j < group_ring.group_order; ++j) 
    {
        group_ring.elements[0][j] = 0;   
    }
    
    for (unsigned int i = 1; i < group_ring.group_ring_order; ++i) 
    {
        unsigned int rem = 0;
        
        for (unsigned int j = 0; j < group_ring.group_order; ++j) 
        {
            unsigned char value = group_ring.elements[i - 1][j] + rem;
            
            if (j == 0) 
            {
                value += 1;
            }
            if (value >= group_ring.ring_order) 
            {
                rem = 1;
                value = 0;
            } else 
            {
                rem = 0;
            }
            
            group_ring.elements[i][j] = value;
        }
    }

    return group_ring;
}

void
print_n_gr_ccl_8b(n_gr_ccl_8b_t *group_ring)
{
    for (unsigned int i = 0; i < group_ring->group_ring_order; ++i) 
    {
        printf("%d: ", i);
        
        for (unsigned int j = 0; j < group_ring->group_order; ++j)  
        {
            printf("%d ", group_ring->elements[i][j]);
        }
        
        printf("\n");
    }
}

void
add_elements_n_gr_ccl_8b(n_gr_ccl_8b_t *group_ring, unsigned int x, unsigned int y, unsigned char *result)
{
    for (unsigned int i = 0; i < group_ring->group_order; ++i)
    {
        result[i] = (group_ring->elements[x][i] + group_ring->elements[y][i]) % group_ring->ring_order;
    }
}

void
multy_elements_n_gr_ccl_8b(n_gr_ccl_8b_t *group_ring, unsigned int x, unsigned int y, unsigned char *result)
{
    for (unsigned int i = 0; i < group_ring->group_order; ++i)
    {
        unsigned char coef = 0;

        for (unsigned int j = 0; j < group_ring->group_order; ++j)
        {
            /*coef += group_ring->elements[x][j]*group_ring->elements[y][sigma_arr[i].p[j]];*/
            coef += group_ring->elements[x][j]*group_ring->elements[y][((i - j) + group_ring->ring_order) % group_ring->ring_order];
        }

        result[i] = coef % group_ring->ring_order;
    }
}

void
free_n_gr_ccl_8b(n_gr_ccl_8b_t *group_ring)
{
    for (unsigned int i = 0; i < group_ring->group_ring_order; ++i)
        free(group_ring->elements[i]);
    
    free(group_ring->elements);
}
