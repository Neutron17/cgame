#include "error.h"
#include <stdio.h>
#include <string.h>

void err(const char *str, const char *file, const char *function, int line, int errn) {
	char buff[128];
	int sz = sprintf(buff, "Error in\n\tfile: %s\n\tfunction: %s\n\tat line: %d\n\terrno: %d, %s\n\tmessage: %s\n",
					 file, function, line, errn, strerror(errn), str);
	fprintf(stderr, "%s\n", buff);
	logToFile(buff, sz);
}
void __err(const char *str, const char *file, const char *function, int line, int errn, const char *arg) {
	char buff[128];
	int sz = sprintf(buff, str, file, function, line, errn, arg);
	fprintf(stderr, "%s\n", buff);
	logToFile(buff, sz);
}

extern char *logFile;

void logToFile(const char *str, int n) {
	FILE *file = fopen(logFile, "r");
	fprintf(file, "%s", str);
	fclose(file);
}