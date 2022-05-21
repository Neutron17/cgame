#include "common.h"
#include <stdio.h>

void afterscanf() {
	int c;
	do {
		c = getchar();
	} while (c != EOF && c != '\n');
}