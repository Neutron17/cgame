#ifndef _NTR_OPTARG_H_
#define _NTR_OPTARG_H_ 1

// Overloading stuff
#define __NARGS(...) __NARGS_(__VA_ARGS__, 5, 4, 3, 2, 1, 0)
#define __NARGS_(_5, _4, _3, _2, _1, N, ...) N
#define __CONC(A, B) __CONC_(A, B)
#define __CONC_(A, B) A##B

#endif //_NTR_OPTARG_H_
