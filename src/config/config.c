#include "config.h"
#include "arr/arr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

char *saveDir = NULL;
struct sermov movs[MOV_SZ] = {
		{true,  {4, 4}, "quitexit", "q", QUIT},
		{false, {2},    "up",       "wu", UP},
		{false, {4},    "down",     "s", DOWN},
		{false, {4},    "left",     "al", LEFT},
		{false, {5},    "right",    "dr", RIGHT},
		{false, {4},    "load",     "", LOAD},
		{false, {4},    "save",     "", SAVE},
		{false, {7},    "restart",  "", RESTART}
};
extern const bool isDebug;

void mkSaveDir();
void loadSaveDir(FILE *file);
void loadMovNames(FILE *file);

void loadConfigs() {
	FILE *file = fopen("config.txt", "r");
	if(!file) {
		if(isDebug)
			fprintf(stderr, "Couldn't open config.txt file, using defaults\n");
	}
	loadSaveDir(file);
	loadMovNames(file);
	fclose(file);
}
const char *LUT[5] = {
		"multiple=%s","size=%s","longs=%s","shorts=%s","type=%s"
};
void loadMovNames(FILE *file) {
	if(!file)
		return;
	char buff[64];
	if(!fgets(buff, 64, file)) {
		fprintf(stderr, "Couldn't read from config\n");
		return;
	}
	if(sscanf(buff, "movNames:%42s", buff) != 1)
		return;
	FILE *movfile = fopen(buff, "r");
	if(!movfile) {
		if(isDebug)
			fprintf(stderr, "Couldn't open movs file %s, using default\n", buff);
		return;
	}
	char val[32];
	for(int i = 0; i < MOV_SZ; i++) {
		movs[i].names = malloc(32);
		movs[i].chnames = malloc(7);
		for(int j = 0;j<6;j++) {
			fgets(buff, 16, movfile);
			if(j == 5)
				continue;
			sscanf(buff, LUT[j], val);
			switch (j) {
				case 0: // multiple
					movs[i].multiple = atoi(val);
					break;
				case 1: // lengths
					movs[i].lens[0] = val[0] - '0';
					if(movs[i].multiple)
						movs[i].lens[1] = val[0] - '0';
					break;
				case 2: // longs
					strncpy(movs[i].names, val, 32);
					break;
				case 3: // shorts
					strncpy(movs[i].chnames, val, 5);
					break;
				case 4:
					if(strncasecmp(val, "quit", 4) == 0 || strncasecmp(val, "exit", 4) == 0) {
						movs[i].type = QUIT;
					} else if(strncasecmp(val, "up", 2) == 0) {
						movs[i].type = UP;
					} else if(strncasecmp(val, "down", 4) == 0) {
						movs[i].type = DOWN;
					} else if(strncasecmp(val, "left", 4) == 0) {
						movs[i].type = LEFT;
					} else if(strncasecmp(val, "right", 5) == 0) {
						movs[i].type = RIGHT;
					} else if(strncasecmp(val, "save", 4) == 0) {
						movs[i].type = SAVE;
					} else if(strncasecmp(val, "load", 4) == 0) {
						movs[i].type = LOAD;
					} else if(strncasecmp(val, "restart", 7) == 0 || strncasecmp(val, "reset", 5) == 0) {
						movs[i].type = RESTART;
					} else {
						movs[i].type = NONE;
					}
					break;
				default:{}
			}
		}
	}
	fclose(movfile);
}

void loadSaveDir(FILE *file) {
	saveDir = alloc(32);
	if(!saveDir) {
		fprintf(stderr, "Couldn't allocate for saveDir\n");
		exit(1);
	}
	if(!file)
		goto def;
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
	// Dir exists
	{
		struct stat sb;
		if(stat(saveDir, &sb) == 0 && S_ISDIR(sb.st_mode)) {
			return;
		} else {
			mkSaveDir();
		}
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
	}
	exit(2);
}