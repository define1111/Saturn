#ifndef _SENTRY_SATURN_PERMUTATION_H_
#define _SENTRY_SATURN_PERMUTATION_H_

typedef struct permutation_tag
{
    int *p;
    int size;
} permutation_t;

permutation_t permutation_multy(const permutation_t *left, const permutation_t *right);
/*permutation_t permutation_degree(const permutation_t *per, int n);*/

permutation_t get_sigma_0(int m);
permutation_t get_pi(int m);

permutation_t *get_pi_arr(int m);
permutation_t *get_sigma_arr(int m);

void print_permutation(const permutation_t *per);

void free_p_arr(permutation_t *per);

#endif