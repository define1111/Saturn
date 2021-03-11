#ifndef _SENTRY_SATURN_NUMERICAL_GROUP_RING_CYCLIC_GROUP_8BIT_H_
#define _SENTRY_SATURN_NUMERICAL_GROUP_RING_CYCLIC_GROUP_8BIT_H_

/* Numerical group ring of cyclic group is Z_m[Z_n]. */

typedef struct numerical_group_ring_cyclic_group_8bit_tag
{
    unsigned char ring_order;
    unsigned char group_order;
    unsigned int group_ring_order;
    unsigned char **elements;
} n_gr_ccl_8b_t;

n_gr_ccl_8b_t init_n_gr_ccl_8b(unsigned char ring_order, unsigned char group_order);
void print_n_gr_ccl_8b(n_gr_ccl_8b_t *group_ring);
void add_elements_n_gr_ccl_8b(n_gr_ccl_8b_t *group_ring, unsigned int x, unsigned int y, unsigned char *result);
void multy_elements_n_gr_ccl_8b(n_gr_ccl_8b_t *group_ring, unsigned int x, unsigned int y, unsigned char *result);
void free_n_gr_ccl_8b(n_gr_ccl_8b_t *group_ring);

#endif