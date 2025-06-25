#include "map.h"
#include "../array/array.h"
#include "../bucket/bucket.h"

#include <malloc.h>

#define MAP_DEF_LENGTH 16
#define MAP_LOAD_FACTOR (double)1.5
#define MAP_CAPCITY_BEFORE_RESIZE (double)0.75

struct map 
{
  array_t bucket_arr;
  hash_func_t hash;
  equal_func_t equal;
  size_t used_buckets;
};

static bool map_cpy(const map_t* map_to_cpy, map_t* source)
{
  for(size_t i = 0; i < ARRAY_LENGTH(map_to_cpy->bucket_arr, bucket_t*); ++i)
  {
  }
}

static bool map_grow_if_above_capacity_threshold(struct map* map)
{
  if(map->used_buckets > (size_t)(MAP_CAPCITY_BEFORE_RESIZE * ARRAY_LENGTH(map->bucket_arr, bucket_t*)))
  {
    array_t new_bucket_arr;
    size_t old_length = ARRAY_LENGTH(map->bucket_arr, bucket_t*);
    if(!ARRAY_INIT(new_bucket_arr, old_length * MAP_LOAD_FACTOR, bucket_t*))
      return false;

        

    
    
  }

  return true;
}

struct map* map_init(hash_func_t hash, equal_func_t equal, size_t length)
{
  struct map* map = malloc(sizeof *map);
  if(map)
  {
    ARRAY_INIT(map->bucket_arr, length, bucket_t*);
    map->equal = equal;
    map->hash = hash;
    map->used_buckets = 0;
  }

  return map;
}

struct map* map_init_simple(hash_func_t hash, equal_func_t equal)
{
  return map_init(hash, equal, MAP_DEF_LENGTH);
}

void map_destroy(map_t* map)
{
  for(size_t i = 0; i < ARRAY_LENGTH(map->bucket_arr,bucket_t*); ++i)
  {
    bucket_destory(ARRAY_AT(map->bucket_arr, i, bucket_t*));
  }
  ARRAY_DESTROY(map->bucket_arr);
  free(map);
}

static bucket_t* map_insert_dont_inc_bucket_count(map_t* map, void* key, void* val)
{
  map_grow_if_above_capacity_threshold(map);
  
  size_t idx = map->hash(key) % ARRAY_LENGTH(map->bucket_arr, bucket_t*);

  //the addresses of the array are surely not NULL so we won't check for that
  bucket_t** key_bucket_head = &ARRAY_AT(map->bucket_arr, idx, bucket_t*);
  bucket_t* key_bucket;

  if(*key_bucket_head)
  {
    if(bucket_find(key_bucket_head, key, &key_bucket, map->equal))
      key_bucket->data = val;

    else 
      key_bucket = bucket_add(key_bucket_head, key, val) ? *key_bucket_head : NULL;
  }

  else 
    key_bucket = bucket_init(key_bucket_head, key, val) ? *key_bucket_head : NULL;

  return key_bucket;
}

bool map_insert(map_t* map, void* key, void* val)
{
  bucket_t* inserted_bucket = map_insert_dont_inc_bucket_count(map, key, val);
  if(inserted_bucket)
  {
    ++map->used_buckets;
  }

  return inserted_bucket != NULL;
}

void map_print(map_t* map, printfunc_t print)
{
  puts("[ \n");
  for(size_t i = 0; i < ARRAY_LENGTH(map->bucket_arr,bucket_t*); ++i)
  {
    bucket_print(&ARRAY_AT(map->bucket_arr, i, bucket_t*), print);
  }
  puts(" ]\n");
}

void* map_get(map_t* map, void* key, bool* is_success)
{
  size_t idx = map->hash(key) % ARRAY_LENGTH(map->bucket_arr, bucket_t*);

  bucket_t** key_bucket_head = &ARRAY_AT(map->bucket_arr, idx, bucket_t*);

  bucket_t* key_bucket;

  if(bucket_find(key_bucket_head, key, &key_bucket, map->equal))
  {
    if(is_success)
      *is_success = true;
    
    return key_bucket->data;
  }
  else
  {
    if(is_success)
      *is_success = false;

    return NULL;
  }
  
}
