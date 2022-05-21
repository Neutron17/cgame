//
// Created by neutron17 on 2022.05.21..
//

#ifndef _NTR_ERROR_H_
#define _NTR_ERROR_H_ 1

#include <errno.h>

#define ERR(str) err(str, __FILE__, __func__, __LINE__, errno)
#define ERR_A(str, args) fprintf(stderr, "Error in\n\tfile: %s\n\tfunction: %s\n\tat line: %d\n\terrno: %d, %s\n\tmessage: "str"\n", \
										__FILE__, __func__, __LINE__, errno, strerror(errno), args)

void logToFile(const char *str, int n);
void err(const char *str, const char *file, const char *function, int line, int errn);
void __err(const char *str, const char *file, const char *function, int line, int errn, const char *arg);

#endif //_NTR_ERROR_H_
