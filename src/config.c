#include "config.h"
#include "arr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *saveDir = NULL;

void loadConfigs() {
	saveDir = alloc(32);
	if(!saveDir) {
		fprintf(stderr, "Couldn't allocate for saveDir\n");
		exit(1);
	}
	FILE *file = fopen("config.txt", "r");
	if(!file) {
		fprintf(stderr, "Couldn't open config.txt file, using default\n");
		goto def;
	}
	char buff[64];
	if(fgets(buff, 64, file) == NULL) {
		fprintf(stderr, "Couldn't read from config\n");
		goto def;
	}
	sscanf(buff, "saveDir:%32s", saveDir);
	goto end;
def:
	strcpy(saveDir, "saves/");
end:
	fclose(file);
}