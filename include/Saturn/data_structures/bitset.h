#ifndef _SENTRY_SATURN_BITSET_H_
#define _SENTRY_SATURN_BITSET_H_

typedef struct bitset_tag
{
    unsigned char *data;
    unsigned int length;
} bitset_t;

#define CHAR_BIT (8)

#define BITMASK(b) (1 << ((b) % CHAR_BIT))
#define BITSLOT(b) ((b) / CHAR_BIT)
#define BITSET(a, b) ((a)[BITSLOT(b)] |= BITMASK(b))
#define BITCLEAR(a, b) ((a)[BITSLOT(b)] &= ~BITMASK(b))
#define BITTEST(a, b) ((a)[BITSLOT(b)] & BITMASK(b))
#define BITNSLOTS(nb) ((nb + CHAR_BIT - 1) / CHAR_BIT)

bitset_t init_bitset(unsigned int length);
void print_bitset(const bitset_t *bitset);
void free_bitset(bitset_t *bitset);

#endif