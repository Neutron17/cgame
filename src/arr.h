#ifndef _NTR_ARRCTOR_H_
#ifndef _NTR_ALL_ARR_H_
#define _NTR_ARRCTOR_H_ 1

#define ARR_SIZE 5
#include <stdbool.h>
#include <stdlib.h>
#include "optarg.h"

// Return values
enum ArrErrors {
    SUCCESS = 0,
    COULDNT_ALLOCATE,
    MAX_ITEMS_REACHED,
    SHR,
    SHR_FREE,
    INC,
    SAME_SZ
};

// Malloc copy
void *alloc(size_t size);
void *acalloc(size_t __nmemb, size_t __size);
// Constructor
__attribute__((used)) enum ArrErrors __attribute__((constructor)) __allocArr_ctor();
// Destructor
__attribute__((used)) enum ArrErrors __attribute__((destructor)) __allocArr_dtor();
// Control methods
enum ArrErrors  allocArr_add (void *n);
enum ArrErrors  allocArr_adds(void *n, ...);
bool            allocArr_in  (const void *n);
bool            allocArr_ins (const void *n, ...);

#define allocArr_pop(...) __CONC(__allocArr_pop, __NARGS(__VA_ARGS__))(__VA_ARGS__)
enum ArrErrors __allocArr_pop1();
enum ArrErrors __allocArr_pop2(int n);
#endif // _NTR_ALL_ARR_H_
#endif //_NTR_ARRCTOR_H_
