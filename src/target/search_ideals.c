#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algebraic_structures/numerical_group_ring_cyclic_group_8bit.h>
#include <data_structures/set.h>
#include <data_structures/bitset_tree.h>

/* temp */
#define RING_ORDER (2)
#define GROUP_ORDER (3)

typedef struct 
{
    int *divisors;
    int size;
} divisors_t;

static divisors_t
get_divisors(int n)
{
    divisors_t div;
    div.size = 0;
    div.divisors = NULL;

    for (int i = 2; i <= n/2; ++i)
    {
        if (n % i == 0)
        {
            div.size++;
            div.divisors = realloc(div.divisors, div.size * sizeof(int));
            div.divisors[div.size - 1] = i;
        }
    }

    return div;
}

int 
main()
{
    n_gr_ccl_8b_t gr = init_n_gr_ccl_8b(RING_ORDER, GROUP_ORDER);
    unsigned char result[GROUP_ORDER];
    divisors_t div = get_divisors(gr.group_ring_order);

    print_n_gr_ccl_8b(&gr);

    for (int i = 0; i < div.size; ++i)
    {
        tree_t tree = init_bitset_tree_iteratively(div.divisors[i] - 1, gr.group_ring_order - 1);
        tree_iterator_t S = init_bitset_tree_iterator(&tree);
        while (S.node)
        {
            set_t *set = get_nums_by_iterator_with_offset(&S);
            int is_subgroup = 1;
            int is_ideal = 1;
            /*printf("Set: ");
            print_set(set);
            printf("\n");*/
            set_iterator_t S1 = init_set_iterator(set);
            while (S1.node) 
            {
                unsigned int data_i = S1.node->data;
                set_iterator_t S2 = S1;
                while (S2.node) {
                    unsigned int data_j = S2.node->data;
                    //printf("(%u, %u)", data_i, data_j);
                    add_elements_n_gr_ccl_8b(&gr, data_i, data_j, result);
                    unsigned int index = result_to_index_n_gr_ccl_8b(&gr, result);
                    is_subgroup = contains(set, index);
                    if (is_subgroup == 0) goto next;
                    next_set_iterator_pos(&S2);
                }
                //printf("\n");
                next_set_iterator_pos(&S1);
            }
            if (is_subgroup)
            {
                set_iterator_t S3 = init_set_iterator(set);          
                while (S3.node)
                {
                    unsigned int data_i = S3.node->data;
                    for (unsigned int j = 2; j < gr.group_ring_order; ++j)
                    {
                        multy_elements_n_gr_ccl_8b(&gr, data_i, j, result);
                        unsigned int index = result_to_index_n_gr_ccl_8b(&gr, result);
                        is_ideal = contains(set, index);
                        if (is_ideal == 0) goto next;
                    }
                    next_set_iterator_pos(&S3);
                }
            }
            if (is_ideal)
            {
                print_set(set);
                printf("\n");
            }
            next:
            next_iterator_pos(&S);
            free_set(&set);
            //printf("\n");
        }
        free_bitset_tree_iterator(&S);
        free_bitset_tree(&tree);
    }

    free(div.divisors);
    free_n_gr_ccl_8b(&gr);
    return 0;
}