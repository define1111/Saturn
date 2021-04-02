#include <stdio.h>

#include <data_structures/set.h>

void
test_set()
{
    set_t *set = NULL;
    add_item_set(&set, 5);
    add_item_set(&set, 2);
    add_item_set(&set, 1);
    add_item_set(&set, 7);
    add_item_set(&set, 4);

    set_iterator_t it = init_set_iterator(set);
    //int i = 0;
    while (it.node)
    {
        /*if (i > 4)
            break;
        ++i;*/
        printf("%u ", it.node->data);
        next_set_iterator_pos(&it);
    }
    printf("\n-----\n");
    print_set(set);
}

int
main()
{
    test_set();

    return 0;
}
