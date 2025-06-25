#include "map.h"

#include <string.h>
#include <stdio.h>

#define MALLOC_VAL(ptr, val) \
  (malloc(sizeof *ptr) && *ptr = val) 

void print_int(void* data)
{
  printf("%d", *(int*)data);
}

size_t hash_int(void* data)
{
  return *(int*)data;
}

bool cmpr_int(void* val1, void* val2)
{
  return *(int*)val1 == *(int*)val2;
}

void print_string(void* data)
{
  printf("%s", (char*)data);
}

bool cmpr_string(void* val1, void* val2)
{
  return !strcmp(val1, val2);
}

int main()
{
  map_t* map = map_init_simple(hash_int, cmpr_int);

  int val = 1;
  int val2 = 2;
  int val3 = 3;
  map_insert(map, &val, &val);
  map_insert(map, &val2, &val2);
  map_insert(map, &val3, &val3);
  map_print(map, print_int);

  int* shouldbeval = map_get(map, &val, NULL);

  printf("for key %d we got val %d\n", val, *shouldbeval);

  map_destroy(map);
  
  return 0;
}
