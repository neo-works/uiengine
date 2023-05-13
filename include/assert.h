#ifndef __UIENGINE_ASSERT_H__
#define __UIENGINE_ASSERT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASSERT_NOT_NULL(element)                            \
    if (element == NULL) {                                  \
        printf("ASSERT_NOT_NULL(failed): '"#element"' is NULL\n");  \
        exit(1);                                            \
    }

#define ASSERT_STR_EQUAL(ptr, val)  \
    if (strcmp(ptr, val) != 0) {                                    \
        printf("ASSERT_STR_EQUAL(failed): '"#ptr"' not equal to '"#val"'\n");\
        exit(1);                                                    \
    }

#endif /* __UIENGINE_ASSERT_H__ */