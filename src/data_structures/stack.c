#include <data_structures/stack.h>
#include <assert.h>

stack_t
init_stack()
{
  stack_t stack;
  stack.head = NULL;
  return stack;
}

void
push(stack_t *stack, stack_info_t info)
{
  stack_node_t *new_node = malloc(sizeof(stack_node_t));
  new_node->data = info;
  new_node->next = stack->head;
  stack->head = new_node;
}

stack_info_t
pop(stack_t *stack)
{
  assert(stack->head && "Failed to pop node from empty stack.");
  stack_info_t info = stack->head->data;
  stack_node_t *old_head = stack->head;
  stack->head = stack->head->next;
  free(old_head);
  return info;
}

int
is_empty(stack_t stack)
{
  return stack.head == NULL;
}

void
free_stack(stack_t *stack)
{
  stack_node_t *node = stack->head;
  while (node)
  {
    stack_node_t *next = node->next;
    free(node);
    node = next;
  }
  stack->head = NULL;
}