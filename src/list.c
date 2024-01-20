#include <list.h>

int nomacro_lpush(List* list, void* item, size_t item_size) {
    void** next = malloc(sizeof(void*) + item_size);
    if(!next) return 1;

    *next = *list;
    memcpy(next + 1, item, item_size);
    *list = next;

    return 0;
}

int nomacro_lpop(List* list) {
    if(!*list) return 1;
    
    List next = lnext(*list);
    free(*list);
    *list = next;
}

void lfree(List list) {
    for(void* next; list; list = next) {
        next = *(void**) list;
        free(list);
    }
}