#include <list.h>

int nomacro_lpush(List* list, void* item, size_t item_size) {
    void** next = malloc(sizeof(void*) + item_size);
    if(!next) return 1;

    *next = *list;
    memcpy(next + 1, item, item_size);
    *list = next;
    return 0;
}

int __compound_lpush(List* list, int n, ...) {
    void* item[n];
    size_t item_size[n];
    size_t total_size = 0;

    va_list args;
    va_start(args, n);
    for(int i = 0; i < n; i++) {
        item[i] = va_arg(args, void*);
        total_size += (item_size[i] = va_arg(args, size_t));
    }
    va_end(args);

    void** next = malloc(sizeof(void*) + total_size),
        *data = next + 1;
    if(!next) return 1;

    *next = *list;
    for(int i = 0; i < n; i++) {
        memcpy(data, item[i], item_size[i]);
        data += item_size[i];
    }
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