#ifndef _NTR_ALL_ARR_H_
#include "arr.h"
#include <stdio.h>
#include <stdarg.h>

typedef struct {
    void **arr;
} Arr;

unsigned used;
unsigned max;
const extern bool isDebug;

Arr arr;
void *alloc(size_t size) {
    void *x = malloc(size);
    if(x != NULL) {
        allocArr_add(x);
    }
    return x;
}
void *acalloc(size_t __nmemb, size_t __size) {
    void *x = calloc(__nmemb, __size);
    if(x != NULL) {
        allocArr_add(x);
    }
    return x;
}

__attribute__((used)) enum ArrErrors __allocArr_ctor() {
    printf("Ctor\n");
    //void **arrr = NULL;
    //arrr = (void**)malloc(1*sz);
    //arrr[0] = (void *)69;
    max = ARR_SIZE;
    arr.arr = (void **)malloc(ARR_SIZE);
    //printf("%p\n", arr->arr);
    if(arr.arr == NULL) {
        if(isDebug)
            printf("Couldn't allocate\n");
        return COULDNT_ALLOCATE;
    }
    used = 0;
    return SUCCESS;
}
__attribute__((used)) enum ArrErrors __allocArr_dtor() {
    if(isDebug)
        printf("dtor\n");
    for(int i = 0; i < used; i++) {
        if(isDebug)
            printf("%p\n", arr.arr[i]);
        if(isDebug) {
            printf("Freeing %d. element\n",
                   i+1);
        }
        free(arr.arr[i]);
        arr.arr[i] = NULL;
    }
    free(arr.arr);
    arr.arr = NULL;
    if(isDebug)
        printf("Successfuly freed all\n");
    return SUCCESS;
}
enum ArrErrors allocArr_add(void *n) {
    if(used == max)
        return MAX_ITEMS_REACHED;
    //	printf("%d\n", *((int*)n));
    //	printf("%p\n", arr.arr);

    arr.arr[used] = n;
    if(isDebug)
        printf("Added %d. element %p\n", used + 1, n);
    used++;
    return SUCCESS;
}
// TODO doesn't work
enum ArrErrors allocArr_adds(unsigned sz, void *n, ...) {
    va_list l;
    va_start(l, n);
    char last = SUCCESS;
    for(int i = 0; i < sz; i++) {
        if((last = allocArr_add(va_arg(l, void *))) != SUCCESS)
        return last;
    }
    va_end(l);
    return SUCCESS;
}
enum ArrErrors __allocArr_pop2(const int n) {
    int last = SUCCESS, count = 0;
    while((last = __allocArr_pop1()) == SUCCESS && count < n)
        count++;
    return last;
}
enum ArrErrors __allocArr_pop1() {
    free(arr.arr[used - 1]);
    arr.arr[used - 1] = NULL;
    used--;
    return SUCCESS;
}
bool allocArr_in(const void *n) {
    for(int i = 0; i < used; i++) {
        if(arr.arr[i] == n)
            return true;
    }
    return false;
}
// TODO: implement with vararg
bool allocArr_ins(const void *n, ...) {
    for(int i = 0; i < used; i++) {
        if(arr.arr[i] == n)
            return true;
    }
    return false;
}
#endif
