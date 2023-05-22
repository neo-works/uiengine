#include "../../include/mem/mem.h"
#include "../../include/assert.h"
#include <stdlib.h>

char *mem_alloc(size_t size) {
    char *ptr = malloc(((size + sizeof(char*)) >> 2) << 2);
    ASSERT_NOT_NULL(ptr);
    return ptr;
}

void mem_free(char *ptr) {
    free(ptr);
}