#include "Stack.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack_node* emplace_back(struct stack_node* head, void* data)
{
  struct stack_node* new_head = malloc(sizeof *new_head);
  
  if(new_head)
  {
    new_head->next = head; 
    new_head->data = data;

    return new_head;
  }

  return head;
}

struct stack_node* pop_back(struct stack_node* head)
{
  if (head)
  {
    struct stack_node* new_head = head->next;
    free(head);
    return new_head;
  }

  return head;
}

void* peak(struct stack_node* head)
{
  if (head)
    return head->data;

  return head;
}

void destroy_stack(struct stack_node* head)
{
  while (head)
  {
    struct stack_node* prev = head;

    head = head->next;
    free(prev);
  }
}

void destroy_stack_full(struct stack_node* head)
{
  while (head)
  {
    struct stack_node* prev = head;

    head = head->next;
    free(prev->data);
    free(prev);
  }
}

void foreach_node(struct stack_node* head, node_func func)
{
  for(struct stack_node* curr = head; curr != NULL; curr = curr->next)
  {
    func(curr->data);
  }
}
