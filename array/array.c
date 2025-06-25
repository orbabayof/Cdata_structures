#include "array.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static void* recalloc(void* ptr, size_t old_size, double load_factor)
{
  size_t new_size = old_size * load_factor;
  void* new_ptr = realloc(ptr, new_size);
  if(new_ptr)
  {
    memset(new_ptr + old_size, 0,new_size - old_size);
    return new_ptr;
  }

  return ptr;
}

bool array_init(struct array* arr, size_t start_size)
{
  if(!arr || !(arr->data = calloc(1,start_size)))
    return false;

  arr->size = start_size;
   return true; 
}

bool array_grow(struct array* arr, double load_factor)
{
  char* new_arr = recalloc(arr->data, arr->size, load_factor);
  if(new_arr)
  {
    arr->data = new_arr;
    arr->size = load_factor * arr->size;
    return true;
  }

  return false;
}

