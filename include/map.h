#ifndef CTIL_MAP_H
#define CTIL_MAP_H

#include "list.h"
#include "vec.h"


typedef void* Map;
#define Map(K, V) struct { K k; V v; }*


Map map(size_t capacity);


int nomacro_minsert(Map* map, void* key, size_t key_size, void* value, size_t value_size);
/**
 * ```cpp
 * int minsert(Map<K, V> map, K key, V value);
 * ```
*/
#define minsert(map, key, value) ({\
_Static_assert /* minsert<K>() */\
    (_Generic(key, typeof((*typeof(map) NULL)->k): 1, default: 0), "Types for map and key do not match");\
_Static_assert /* minsert<V>() */\
    (_Generic(value, typeof((*typeof(map) NULL)->v): 1, default: 0), "Types for map and value do not match");\
    nomacro_minsert((void*) (map), (void*) &(typeof(key)[]) { key }, sizeof(key), (void*) &(typeof(value)[]) { value }, sizeof(value)); })


void* nomacro_mget(Map* map, void* key, size_t key_size);
/**
 * ```cpp
 * V* mget(Map<K, V> map, K key);
 * ```
*/
#define mget(map, key) ({\
_Static_assert /* minsert<K>() */\
    (_Generic(key, typeof((*typeof(map) NULL)->k): 1, default: 0), "Types for map and key do not match");\
    (typeof((*typeof(map) NULL)->k)*) nomacro_mget((void*) (map), (void*) &(typeof(key)[]) { key }, sizeof(key)); })


#endif