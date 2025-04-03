#include "bucket.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


//dummy function helper
static void do_not_destroy__(void*) {}


bool bucket_init(struct bucket** head, void* key, void* val)
{
  if(head)
  {
    struct bucket* new_head = *head = malloc(sizeof(struct bucket));
    new_head->next = nullptr; 
    new_head->key = key;
    new_head->data = val;

    return new_head;
  }

  return false;
}

bool bucket_add(struct bucket** head, void* key, void* val)
{
  struct bucket* new_head = malloc(sizeof(struct bucket));
  if(new_head)
  {
    new_head->data = val;
    new_head->key = key;
    new_head->next = *head;

    *head = new_head;

    return true;
  }

  return false;
}

bool bucket_find(struct bucket** head, void* key, struct bucket** ret_bucket, cmpfunc_t equal)
{
  struct bucket* curr = *head;
  while(curr)
  {
    if(equal(key, curr->key)) 
    {
      if(ret_bucket)
      {
        *ret_bucket = curr;

      }
      return true;
    }
    curr = curr->next;
  }

  return false;
}

void bucket_print(struct bucket** bucket, printfunc_t print)
{

  bool comma = false;

  printf("{ ");
  for(struct bucket* curr = *bucket; curr != nullptr; curr = curr->next)  
  {
    if(comma)
    {
      printf(", ");
    }
    else 
      comma = true;

    print(curr->data);
  }

  printf(" }\n");
}


static void bucket_destroy__(struct bucket* head, void (*destory_data_func)(void*))
{
  while(head)
  {
    struct bucket* next = head->next;
    destory_data_func(head->data);
    free(head);
    head = next;
  }
  free(head);
}


void bucket_destory(struct bucket* head)
{
  //calls nothing on the data
  bucket_destroy__(head, do_not_destroy__);
}

void bucket_destroy_full(struct bucket* head)
{
  //calls free on the data
  bucket_destroy__(head, free);
}


bool bucket_delete__(struct bucket** head, void* key, cmpfunc_t equal, void (*destory_data_func)(void*) )
{

  if(!head)
    return false;


  struct bucket* curr = *head;
  struct bucket* prev = curr;

  while(curr)
  {
    if(equal(key, curr->key)) 
    {
      if(curr != *head)
      {
        prev->next = curr->next;
      }
      else 
      {
        *head = (*head)->next;
      }

      destory_data_func(curr->data);
      free(curr);

      return true;
    }
    prev = curr;
    curr = curr->next;
  }

  return false;
}



bool bucket_delete_full(struct bucket** head, void* key, cmpfunc_t equal)
{
  return bucket_delete__(head, key, equal, free);
}

bool bucket_delete(struct bucket** head, void* key, cmpfunc_t equal)
{
  return bucket_delete__(head, key, equal, do_not_destroy__);
}
