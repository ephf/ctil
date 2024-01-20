#ifndef CTIL_MAP_H
#define CTIL_MAP_H

#include <list.h>
#include <vec.h>
#include <stdint.h>


typedef void* Map;
/**
 * ```java
 * : Sized
 * ```
*/
#define Map(K, V) struct { K k; V v; }*


size_t __fnv_1a_hash(void* data, size_t data_size);

#define __map_key_generic(key) _Generic(key,\
    char*: (void*) key,\
    default: (void*) &(typeof(key)[]) { key })

#define __map_key_size_generic(key) _Generic(key,\
    char*: strlen(key),\
    default: sizeof(key))

#define __map_type_arg(map, arg) typeof(((typeof(map)) NULL)->arg)


Map map(size_t capacity);


int nomacro_minsert(Map* map, void* key, size_t key_size, void* value, size_t value_size);
/**
 * ```cpp
 * int minsert(Map<K, V> map, K key, V value);
 * ```
*/
#define minsert(map, key, value) ({\
_Static_assert /* minsert<K>() */\
    (_Generic(key, __map_type_arg(*map, k): 1, default: 0), "Types for map and key do not match");\
_Static_assert /* minsert<V>() */\
    (_Generic(value, __map_type_arg(*map, v): 1, default: 0), "Types for map and value do not match");\
    nomacro_minsert((void*) (map), __map_key_generic(key), __map_key_size_generic(key), (void*) &(typeof(value)[]) { value }, sizeof(value)); })


void* nomacro_mget(Map map, void* key, size_t key_size);
/**
 * ```cpp
 * V* mget(Map<K, V> map, K key);
 * ```
*/
#define mget(map, key) ({\
_Static_assert /* minsert<K>() */\
    (_Generic(key, __map_type_arg(map, k): 1, default: 0), "Types for map and key do not match");\
    (__map_type_arg(map, v)*) nomacro_mget((void*) (map), __map_key_generic(key), __map_key_size_generic(key)); })


void mfree(Map map);


#endif