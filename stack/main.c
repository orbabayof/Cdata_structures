#include "Stack.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_int_stack(void* data)
{
  if(data) 
  {
    printf("%d\n", *(int*)data); 
  }
}

void print_string_stack(void* data)
{
  if(data) 
  {
    printf("%s\n", (char*)data); 
  }
}

void test_int_stack()
{
  struct stack_node* stack = NULL;
  for(int i = 0; i < 5; ++i)
  {
    int* num = malloc(sizeof(int));
    if(num)
      *num = 5;
    stack = emplace_back(stack, num);
  }

  foreach_node(stack, print_int_stack);

  destroy_stack_full(stack);
}

void test_string_stack()
{
  struct stack_node* stack = NULL;

  stack = emplace_back(stack, "hello");
  stack = emplace_back(stack, "world");

  foreach_node(stack, print_string_stack);

  destroy_stack(stack);
  
  
}


int main()
{
  test_int_stack();

  return EXIT_SUCCESS;
}
