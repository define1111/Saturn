#include <stdlib.h>
#include <stdio.h>

/*#include "../../include/Saturn/algebraic_structures/permutation.h"*/
#include <algebraic_structures/permutation.h>

permutation_t
permutation_multy(const permutation_t *left, const permutation_t *right)
{
    permutation_t result;

    result.size = left->size;
    result.p = malloc(result.size * sizeof(int));

    for (int i = 0; i < result.size; ++i)
    {
        result.p[i] = left->p[right->p[i]];
    }

    return result;
}

permutation_t 
get_sigma_0(int m)
{
    permutation_t sigma_0;

    sigma_0.size = m;
    sigma_0.p = malloc(sigma_0.size * sizeof(int));
    sigma_0.p[0] = 0;

    for (int i = 1; i < sigma_0.size; ++i)
        sigma_0.p[i] = m - i; 

    return sigma_0;
}

permutation_t 
get_pi(int m)
{
    permutation_t pi;

    pi.size = m;
    pi.p = malloc(pi.size * sizeof(int));
    pi.p[0] = m - 1;

    for (int i = 1; i < pi.size; ++i)
        pi.p[i] = i - 1; 

    return pi;
}

permutation_t *
get_pi_arr(int m)
{
    permutation_t *pi_arr = malloc(m * sizeof(permutation_t));

    for (int i = 0; i < m; ++i)
    {
        pi_arr[i].size = m;
        pi_arr[i].p = malloc(m * sizeof(int));
    }
    
    for (int i = 0; i < m; ++i)
        pi_arr[0].p[i] = i;

    pi_arr[1] = get_pi(m);

    /*pi_arr[2] = permutation_multy(&pi_arr[1], &pi_arr[1]);
    pi_arr[3] = permutation_multy(&pi_arr[2], &pi_arr[1]);
    pi_arr[4] = permutation_multy(&pi_arr[3], &pi_arr[1]);*/

    for (int i = 2; i < m; ++i)
        pi_arr[i] = permutation_multy(&pi_arr[i-1], &pi_arr[1]);

    return pi_arr;
}

permutation_t *
get_sigma_arr(int m)
{
    permutation_t *pi_arr = get_pi_arr(m);
    permutation_t *sigma_arr = malloc(m * sizeof(permutation_t));

    for (int i = 0; i < m; ++i)
    {
        sigma_arr[i].size = m;
        sigma_arr[i].p = malloc(m * sizeof(int));
    }

    sigma_arr[0] = get_sigma_0(m);

    for (int i = 1; i < m; ++i)
        sigma_arr[i] = permutation_multy(&sigma_arr[0], &pi_arr[i]);

    free_p_arr(pi_arr);

    return sigma_arr;
}

void
free_p_arr(permutation_t *per)
{
    for (int i = 0; i < per[i].size; ++i)
        free(per[i].p);
    free(per);
}

void 
print_permutation(const permutation_t *per)
{
    printf("[ ");

    for (int i = 0; i < per->size; ++i)
        printf("%d ", per->p[i]);

    printf("]\n");
}


/*void
permutation_multy_save_to_left(permutation_t *left, const permutation_t *right)
{
    int *tmp = malloc(left->size * sizeof(int));

    for (int i = 0; i < left->size; ++i)
    {
        tmp[i] = left->p[i];
    }

    for (int i = 0; i < left->size; ++i)
    {   
        left->p[i] = tmp[right->p[i]];
    }

    free(tmp);
}

permutation_t
permutation_degree(const permutation_t *per, int n)
{
    permutation_t result;

    result.size = per->size;
    result.p = malloc(result.size * sizeof(int));

    for (int i = 0; i < n; ++i)
    {
        result.p[i] = per->p[i];
    }

    for (int i = 1; i < n; ++i)
    {
        permutation_multy_save_to_left(&result, per);
    }

    return result;
}*/