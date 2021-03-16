#include <stdio.h>
#include <stdlib.h>

#include <data_structures/bitset.h>

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
main()
{
    test_null_bitset();

    test_set_bitset();

    return 0;
}