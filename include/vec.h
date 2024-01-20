#ifndef CTIL_VEC_H
#define CTIL_VEC_H

#include <stdlib.h>
#include <string.h>


typedef void* Vec;
/**
 * ```java
 * : Sized
 * ```
*/
#define Vec(T) T*

typedef struct {
    size_t capacity;
    size_t size;
} VecHeader;

/**
 * ```cpp
 * VecHeader* vheader(Vec<T> vec);
 * ```
*/
#define vheader(vec) ((VecHeader*)(void*) (vec) - 1)

/**
 * ```cpp
 * size_t vsize(Vec<T> vec);
 * ```
*/
#define vsize(vec) (vsheader(vec)->size)


Vec vec(size_t capacity);


// use `vresize()`
int nomacro_vresize(Vec* vec, size_t capacity);
/**
 * ```cpp
 * int vresize(Vec<T> vec, size_t capacity);
 * ```
*/
#define vresize(vec, capacity) \
    nomacro_vresize((void*) (vec), capacity * sizeof(**(vec)))


// use `vpush()`
int nomacro_vpush(Vec* vec, void* item, size_t item_size);
/**
 * ```cpp
 * int vpush(Vec<T> vec, T item);
 * ```
*/
#define vpush(vec, item) ({\
_Static_assert /* vpush<T>() */\
    (_Generic(item, typeof(**(vec)): 1, default: 0), "Types for vector and item do not match");\
    nomacro_vpush((void*) (vec), (void*) &(typeof(item)[]) { item }, sizeof(item)); })


// use `vpop()`
int nomacro_vpop(Vec* vec, size_t item_size);
/**
 * ```cpp
 * int vpop(Vec<T> vec);
 * ```
*/
#define vpop(vec) \
    nomacro_vpop((void*) (vec), sizeof(**(vec)))


int nomacro_vunshift(Vec* vec, void* item, size_t item_size);
/**
 * ```cpp
 * int vunshift(Vec<T> vec, T item);
 * ```
*/
#define vunshift(vec, item) ({\
_Static_assert /* vunshift<T>() */\
    (_Generic(item, typeof(**(vec)): 1, default: 0), "Types for vector and item do not match");\
    nomacro_vunshift((void*) (vec), (void*) &(typeof(item)[]) { item }, sizeof(item)); })


int nomacro_vshift(Vec* vec, size_t item_size);

#define vshift(vec, item) \
    nomacro_vshift((void*) (vec), sizeof(item))


#endif