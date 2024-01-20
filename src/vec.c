#include <vec.h>

Vec nomacro_vec(size_t capacity) {
    VecHeader* header = malloc(sizeof(VecHeader) + capacity);
    if(!header) return NULL;

    *header = (VecHeader) { capacity, 0 };
    return (void*) (header + 1);
}

int nomacro_vresize(Vec* vec, size_t capacity) {
    VecHeader* header = vheader(*vec);
    header->capacity = capacity;
    header = realloc(header, sizeof(VecHeader) + capacity);
    if(!header) return 1;

    *vec = (void*) (header + 1);
    return 0;
}

int nomacro_vpush(Vec* vec, void* item, size_t item_size) {
    VecHeader* header = vheader(*vec);
    if(header->size + item_size > header->capacity) {
        if(!header->capacity) header->capacity = item_size;
        while((header->capacity *= 2) < header->size + item_size)
            ;;
        if(nomacro_vresize(vec, header->capacity)) return 1;
        header = vheader(*vec);
    }

    memcpy(*vec + header->size, item, item_size);
    header->size += item_size;
    return 0;
}

int nomacro_vpop(Vec* vec, size_t item_size) {
    vheader(*vec)->size -= item_size;
    return vheader(*vec)->size - item_size < 0;
}

int nomacro_vunshift(Vec* vec, void* item, size_t item_size) {
    VecHeader* header = vheader(*vec);
    if(header->size + item_size > header->capacity) {
        if(!header->capacity) header->capacity = item_size;
        while((header->capacity *= 2) < header->size + item_size)
            ;;
        if(nomacro_vresize(vec, header->capacity)) return 1;
        header = vheader(*vec);
    }

    memmove(*vec + item_size, *vec, header->size);
    memcpy(*vec, item, item_size);
    header->size += item_size;
    return 0;
}

int nomacro_vshift(Vec* vec, size_t item_size) {
    if(nomacro_vpop(vec, item_size)) return 1;
    memmove(*vec, *vec + item_size, vheader(*vec)->size);
    return 0;
}

void vfree(Vec vec) {
    free((VecHeader*) vec - 1);
}