#ifndef STRIKE_STACK_H
#define STRIKE_STACK_H

#include <stdbool.h>
#include <stddef.h>

struct stack_node
{
  struct stack_node* next;
  void* data;
};

// will own the data
struct stack_node* emplace_back(struct stack_node* head, void* data);

struct stack_node* pop_back(struct stack_node* head);

void* peak(struct stack_node* head);

void destroy_stack(struct stack_node* head);
void destroy_stack_full(struct stack_node* head);

typedef void (*node_func)(void*);

void foreach_node(struct stack_node* head, node_func func);

#endif
