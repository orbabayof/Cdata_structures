#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef size_t (*hashfunc_t)(void*);
typedef void (*printfunc_t)(void*);
typedef bool (*cmpfunc_t)(void* val1, void* val2);

typedef struct bucket bucket_t;

bool bucket_init(struct bucket** head, void* key, void* val);

void bucket_print(struct bucket** bucket, printfunc_t print);

bool bucket_add(struct bucket** head, void* key, void* val);
bool bucket_find(struct bucket** head, void* key, struct bucket** ret_bucket, cmpfunc_t equal);



void bucket_destory(struct bucket*);


bool bucket_delete(struct bucket** head, void* key, cmpfunc_t equal);
bool bucket_delete_full(struct bucket** head, void* key, cmpfunc_t equal);

struct bucket
{
  void* data;
  void* key;
  
  struct bucket* next;
};
