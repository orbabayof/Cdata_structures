#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef size_t (*hashfunc_t)(void*);
typedef void (*printfunc_t)(void*);
typedef bool (*cmpfunc_t)(void* val1, void* val2);

typedef struct bucket bucket_t;

bool bucket_init(struct bucket** head, size_t hash_code, void* val);

void bucket_print(struct bucket** bucket, printfunc_t print);

bool bucket_add(struct bucket** head, size_t hash_code, void* val);

bool bucket_find(struct bucket** head, size_t hash_code, void* val, struct bucket** ret_bucket, cmpfunc_t equal);

bool bucket_data_remove(struct bucket** head, void* data); 
bool bucket_data_remove_unalloc(struct bucket** head, void* data); 

void bucket_destory(struct bucket*);

bool bucket_delete(struct bucket** head, size_t hash_code, void* val, cmpfunc_t equal);
bool bucket_delete_full(struct bucket** head, size_t hash_code, void* val, cmpfunc_t equal);

struct bucket
{
  void* data;
  size_t hash_code;
  
  struct bucket* next;
};
