#include <map.h>

// http://www.isthe.com/chongo/tech/comp/fnv/#FNV-1a
size_t __fnv_1a_hash(void* data, size_t data_size) {
    uint64_t hash = 14695981039346656037UL;
    while(data_size--)
        hash = (hash ^ ((uint8_t*) data)[data_size]) *  1099511628211UL;
    return hash;
}

Map map(size_t capacity) {
    Vec(List) map = vec(List, capacity);
    memset(map, 0, vheader(map)->capacity);
    return map;
}

int nomacro_minsert(Map* map, void* key, size_t key_size, void* value, size_t value_size) {
    return __compound_lpush(
        ((List*) *map) + __fnv_1a_hash(key, key_size) % (vheader(*map)->capacity / sizeof(List)), 2,
        key, key_size, value, value_size
    );
}

void* nomacro_mget(Map map, void* key, size_t key_size) {
    lforeachref(((List*) map)[__fnv_1a_hash(key, key_size) % (vheader(map)->capacity / sizeof(List))], void* entry_key) {
        if(!memcmp(key, entry_key, key_size))
            return entry_key + key_size;
    }
    return NULL;
}

void mfree(Map map) {
    for(int i = 0; i < vheader(map)->capacity / sizeof(List); i++)
        lfree(((List*) map)[i]);
    vfree(map);
}