#include <stdlib.h>
#include <stdio.h>

#include <math.h>

/*#include <algebraic_structures/permutation.h>*/

#include <algebraic_structures/numerical_group_ring_cyclic_group_8bit.h>

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
    /*sigma_arr = get_sigma_arr(group_ring->group_order);*/

    for (unsigned int i = 0; i < group_ring->group_order; ++i)
    {
        unsigned char coef = 0;

        for (unsigned int j = 0; j < group_ring->group_order; ++j)
        {
            /*coef += group_ring->elements[x][j]*group_ring->elements[y][sigma_arr[i].p[j]];*/
            coef += group_ring->elements[x][j]*group_ring->elements[y][((i - j) + group_ring->group_order) % group_ring->group_order];
        }

        result[i] = coef % group_ring->ring_order;
    }

    /*free_p_arr(sigma_arr);*/
}

unsigned int
result_to_index_n_gr_ccl_8b(n_gr_ccl_8b_t *group_ring, unsigned char *result)
{
    unsigned int i = 0;
    int flag = 0;

    for (; i < group_ring->group_ring_order; ++i)
    {
        for (unsigned int j = 0; j < group_ring->group_order; ++j)
        {
            if (group_ring->elements[i][j] != result[j])
            {
                flag = 0;
                break;
            }
            else
            {
                flag = 1;
            }
        }

        if (flag)
            return i;
    }

    return group_ring->group_ring_order + 1;
}

void
free_n_gr_ccl_8b(n_gr_ccl_8b_t *group_ring)
{
    for (unsigned int i = 0; i < group_ring->group_ring_order; ++i)
        free(group_ring->elements[i]);
    
    free(group_ring->elements);
}
