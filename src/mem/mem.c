#include "../../include/mem/mem.h"
#include <stdlib.h>

char *mem_alloc(size_t size) {
    return malloc(size);
}

void mem_free(char *ptr) {
    free(ptr);
}