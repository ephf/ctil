#ifndef CTIL_LIST_H
#define CTIL_LIST_H

#include <stdlib.h>
#include <string.h>


typedef void* List;
/**
 * ```cpp
 * List<T>
 * ```
*/
#define List(T) T*

/**
 * ```cpp
 * List<T> list();
 * ```
*/
#define list() NULL


// use `lpush()`
int nomacro_lpush(List* list, void* item, size_t item_size);
/**
 * ```cpp
 * int lpush(List<T>* list, T item);
 * ```
*/
#define lpush(list, item) ({\
_Static_assert /* lpush<T>() */\
    (_Generic(item, typeof(**(list)): 1, default: 0), "Types for list and item do not match");\
    nomacro_lpush((void*) (list), (void*) &(typeof(item)[]) { item }, sizeof(item)); })


// use `lpop()`
int nomacro_lpop(List* list);
/**
 * ```cpp
 * int lpop(List<T>* list);
 * ```
*/
#define lpop(list) \
    nomacro_lpop((void*) (list))


void lfree(List list);


/**
 * ```cpp
 * T* ltop(List<T> list);
 * ```
*/
#define ltop(list) \
    ((typeof(list))(void*) ((void**)(void*) (list) + 1))


/**
 * ```cpp
 * List<T> lnext(List<T> list);
 * ```
*/
#define lnext(list) \
    ((typeof(list))(void*) (*(void**)(void*) list))


#define lforeach(list, decl) \
    for(void** __list = (void*) (list), *__ = __list; __list; __ = __list = *__list)\
    for(decl = *(typeof(list))(void*) (__list + 1); __; __ = NULL)

#define lforeachref(list, decl) \
    for(void** __list = (void*) (list), *__ = __list; __list; __ = __list = *__list)\
    for(decl = (void*) (__list + 1); __; __ = NULL)


#endif