#ifndef _NTR_COMMON_H_
#define _NTR_COMMON_H_ 1

#include <errno.h>
#include <stdbool.h>
#include <ncurses.h>

#define VERSION 1.3

#define printf printw
void afterscanf();
bool file_exists(const char *filename);

#endif //_NTR_COMMON_H_
