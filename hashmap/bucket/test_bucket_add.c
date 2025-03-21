#include "bucket.h"

#include <stdio.h>

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

int main()
{
  bucket_t* bucket;
  int val1 = 1;
  bucket_init(&bucket, 1, &val1);
  int val2 = 2;
  int val3 = 3;
  int val4 = 4;
  int key = 1;

  bucket_add(&bucket, 1, &val2);
  bucket_add(&bucket, 1, &val3);
  bucket_add(&bucket, 1, &val4);

  printf("bucket: ");
  bucket_print(&bucket, print_int);

  bucket_t* found;

  if(bucket_find(&bucket, key, &val1, &found, cmpr_int))
    puts("val1 found");
  bucket_delete(&bucket, 1, &val3, cmpr_int);

  bucket_print(&bucket, print_int);


  bucket_destory(bucket);
  return 0;
}
