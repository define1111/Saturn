#include <stdio.h>
#include <stdlib.h>

#include <data_structures/bitset.h>
#include <data_structures/bitset_tree.h>

void
test_null_bitset()
{
    for (unsigned int i = 1; i <= 16; ++i)
    {
        bitset_t bs_ibit = init_bitset(i);
        print_bitset(&bs_ibit);
        free_bitset(&bs_ibit);
    }
}

void
test_set_bitset()
{
    for (unsigned int i = 1; i <= 16; ++i)
    {
        bitset_t bs_ibit = init_bitset(i);
        BITSET(bs_ibit.data, i - 1);
        print_bitset(&bs_ibit);
        free_bitset(&bs_ibit);
    }
}

int
factorial(unsigned int n)
{
    unsigned int f = 1;
    for (unsigned int i = 1; i <= n; ++i)
        f *= i;
    return f;
}

void
test_bitset_tree()
{
    tree_t tree = init_bitset_tree(3, 5);
    print_bitset_tree(&tree);
    free_bitset_tree(&tree);
}

int
main()
{
    test_null_bitset();

    test_set_bitset();

    test_bitset_tree();

    return 0;
}