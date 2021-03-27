#include <stdlib.h>
#include <stdio.h>

#include <data_structures/bitset.h>

bitset_t 
init_bitset(unsigned int length)
{
    bitset_t bitset;

    bitset.data = (unsigned char *) calloc(BITNSLOTS(length) * CHAR_BIT, CHAR_BIT);
    bitset.length = length;

    return bitset;
}

void 
print_bitset(const bitset_t *bitset)
{
    for (unsigned int i = 0; i < bitset->length; ++i)
    {
        printf("%u", !!(BITTEST(bitset->data, i)));
    }

    printf("\n");
}

void
free_bitset(bitset_t *bitset)
{
    free(bitset->data);
}