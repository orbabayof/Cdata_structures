#pragma once

#include "../bucket/bucket.h"

#include <stdbool.h>

typedef struct map map_t;

typedef size_t (*hash_func_t)(void* key);
typedef bool (*equal_func_t)(void* key1, void* key2);

map_t* map_init(hash_func_t hash, equal_func_t equal, size_t length);

map_t* map_init_simple(hash_func_t hash, equal_func_t equal);

void map_destroy(map_t* map);
void map_print(map_t* map, printfunc_t print);
bool map_insert(map_t* map, void* key, void* val);

void* map_get(map_t* map, void* key, bool* is_seccess);
