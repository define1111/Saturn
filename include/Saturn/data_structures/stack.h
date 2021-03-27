#ifndef _SENTRY_SATURN_STACK_H_
#define _SENTRY_SATURN_STACK_H_
#include <data_structures/bitset_tree.h>

typedef struct stack_node
{
  stack_info_t data;
  struct stack_node *next;
} stack_node_t;

typedef struct stack
{
  stack_node_t *head;
} stack_t;

stack_t init_stack();
void push(stack_t *stack, stack_info_t info);
stack_info_t pop(stack_t *stack);
int is_empty(stack_t stack);
void free_stack(stack_t *stack);

#endif