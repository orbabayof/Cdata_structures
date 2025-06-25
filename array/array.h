#pragma once

typedef struct array array_t;

#include <stddef.h>
#include <stdbool.h>
#include <malloc.h>

struct array
{
  char* data;
  size_t size;
};


bool array_init(struct array* arr, size_t start_size);
bool array_grow(struct array* arr, double load_factor);

#define ARRAY_AT(arr, idx, type) \
  ((type*)(arr.data))[idx]

#define ARRAY_INIT(arr, length, type) \
  array_init(&arr, (length) * sizeof(type))

#define ARRAY_GROW(arr, load_factor) \
  array_grow(&(arr), load_factor)

#define ARRAY_LENGTH(arr, type) \
  ((arr).size / sizeof(type))

#define ARRAY_DESTROY(arr) \
  free(arr.data)
