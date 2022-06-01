#include "arr.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <getopt.h>
#include <sys/stat.h>
#include <ncurses.h>
#include <unistd.h>
#include "config.h"
#include "movement.h"
#include "position.h"
#include "entity.h"
#include "common.h"
#include "exitCodes.h"
#include "args.h"
#include "error.h"
#include "editor/editor.h"

bool isDebug = false;
bool running = true;
bool beforeAlloc = false;

void printBoard();
unsigned parseArgs(int argc, char *argv[]);

#define PL_ICON 'X'
#define BX_ICON 'W'
#define TIMES_MAX 10
#define newBox(x,y) addEntity((entity) { { x, y }, BX_ICON, true, false, BOX})

int main(int argc, char *argv[]) {
	initscr();
	noecho();
	curs_set(FALSE);
	keypad(stdscr, TRUE);
	srandom(time(NULL));
	unsigned args = parseArgs(argc, argv);
	if((args & A_EDIT) == A_EDIT) {
		editor();
		return EX_SUCC;
	}
	loadConfigs(args);
	entity pl = (entity) { ((pos) {1, 2}), PL_ICON, false, true, DEF };
	setUpEntity(50, &pl);
	/*printf("Load[0] or create new[1]?\n");
	switch (getchar()) {
		case '0':
			printf("Name: ");
			char buff[16];
			scanf("%15s", buff);
			if (!loadEntities(buff, &pl)) {
				break;
			}
		default:
			fprintf(stderr, "Invalid option, new game\n");
		case '1':*/
	for (int i = 0; i < 9; i++) {
		pos tmp = unusedPos();
		newBox(tmp.y, tmp.x);
	}
	pos tmp = unusedPos();
	addEntity((entity) {{tmp.y, tmp.x}, 'O', false, true, FIN});
	enum Movement mov;
	int times = 0;
	char buff[32] = "", str[16] = "", arg[7] = "";
	printBoard();
	while (running) {
input:
		getnstr(buff, 32);
		/*if(fgets(buff, 32, stdin) == NULL) {
			fprintf(stderr, "No input\n");
			goto input;
		}*/
		sscanf(buff, "%15s %d", str, &times);
		if ((mov = strToMov(str)) == NONE) {
			printw("Invalid option\n");
			goto input;
		}
		if(times < 1)
			times = 1;
		else if(times > TIMES_MAX)
			times = TIMES_MAX;
		for(int i = 0; i < times; i++) {
			n_move(&pl, mov);
		}
		strcpy(str, "");
		strcpy(arg, "");
		times = 1;
		clear();
		printBoard();
	}
	endwin();
	return EX_SUCC;
}

extern char *logFile;
unsigned parseArgs(int argc, char *argv[]) {
	int c;
	int args = 0;
	while((c = getopt(argc, argv, "Vdvhl:s:e")) != -1) {
		switch(c) {
			case 'v':
			case 'd':
				isDebug = true;
				break;
			case 'V':
				fprintf(stdout, "Version: %f\n", VERSION);
				beforeAlloc = true;
				exit(0);
			case 'h':
				puts("-V: version\n"
					 "-v or -d: debug\n"
					 "-l <arg(32)>: set logfile\n"
					 "-s <arg(32)>: set save directory\n"
					 "-e: launch editor");
				break;
			case 'l': {
				logFile = alloc(32);
				if(file_exists(optarg) && strnlen(optarg, CONF_LEN+1) < CONF_LEN) {
					strncpy(logFile, optarg, CONF_LEN);
				} else {
					strncpy(logFile, "log.txt", 7);
				}
				args |= A_LOG;
				break;
			}
			case 's': {
				saveDir = alloc(32);
				{
					struct stat sb;
					if (strnlen(optarg, CONF_LEN+1) < CONF_LEN && stat(optarg, &sb) == 0 && S_ISDIR(sb.st_mode)) {
						strncpy(saveDir, optarg, CONF_LEN);
					} else {
						strncpy(saveDir, "saves/", 5);
					}
				}
				args |= A_SDIR;
				break;
			}
			case 'e':
				args |= A_EDIT;
				break;
			default:
				fprintf(stderr, "Unknown argument\n");
				exit(EX_UNK_ARG);
		}
	}
	return args;
}

void printBoard() {
	for(int i = 0; i<B_WID+2;i++)
		printw("-");
	printw("\n");
	for(int y = 0; y < B_HEI; y++) {
		printw("|");
		for (int x = 0; x < B_WID; x++) {
			printw("%c", iconAtPos((pos){y,x}));
		}
		printw("|\n");
	}
	for(int i = 0; i<B_WID+2;i++)
		printw("-");
	printw("\n");
	refresh();
}
