#include "bucket.h"

#include <stdio.h>
#include <string.h>

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
  bucket_t* bucket;

  bucket_init(&bucket, "1", "val1");


  if(!bucket_delete(&bucket, "1", cmpr_string))
    puts("not good");

  bucket_print(&bucket, print_string);


  bucket_destory(bucket);
  return 0;
}
