#include "common.h"
#include <stdio.h>
#include <sys/stat.h>

void afterscanf() {
	int c;
	do {
		c = getchar();
	} while (c != EOF && c != '\n');
}
bool file_exists(const char *filename) {
	struct stat buffer;
	return (stat (filename, &buffer) == 0);
}