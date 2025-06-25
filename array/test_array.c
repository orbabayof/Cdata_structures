#include "array.h"
#include <malloc.h>

#include <stdio.h>
int main()
{
  array_t array;
  ARRAY_INIT(array, 3, int);

  ARRAY_AT(array, 2, int) = 1;

  array_grow(&array, 9);

  for(size_t i = 0; i < ARRAY_LENGTH(array, int); ++i)
  {
    printf("%d \n", ARRAY_AT(array, i, int));
  }

  printf("%d \n", ARRAY_AT(array, 1, int));
  ARRAY_DESTROY(array);
  return 0;
}
