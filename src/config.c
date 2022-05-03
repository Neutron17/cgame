#include "config.h"
#include "arr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

char *saveDir = NULL;
extern const bool isDebug;

void mkSaveDir();

void loadConfigs() {
	saveDir = alloc(32);
	if(!saveDir) {
		fprintf(stderr, "Couldn't allocate for saveDir\n");
		exit(1);
	}
	FILE *file = fopen("config.txt", "r");
	if(!file) {
		if(isDebug)
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
	struct stat sb;
	// Dir exists
	if(stat(saveDir, &sb) == 0 && S_ISDIR(sb.st_mode)) {
		return;
	} else {
		mkSaveDir();
	}
}
void mkSaveDir() {
	if(isDebug)
		printf("Creating save dir\n");
	switch (mkdir(saveDir, S_IRWXU)) {
		case EACCES:
			fprintf(stderr, "The program doesn't have access to the save directory\n");
			break;
		case EEXIST:
			return;
		case ENAMETOOLONG:
			fprintf(stderr, "Save directory too long\n");
			break;
		default:
			break;
	};
	exit(2);
}