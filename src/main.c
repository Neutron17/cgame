#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "config.h"
#include "arr.h"
#include "movement.h"
#include "position.h"
#include "entity.h"
#include "common.h"

const bool isDebug = false;
bool running = true;

void printBoard();

#define PL_ICON 'X'
#define BX_ICON 'W'
#define TIMES_MAX 10
#define newBox(x,y) addEntity((entity) { { x, y }, BX_ICON, true, BOX})

int main(int argc, const char *argv[]) {
	srandom(time(NULL));
	loadConfigs();
	entity pl = (entity) { ((pos) {1, 2}), PL_ICON, false, DEF };
	setUpEntity(9, &pl);
	printf("Load[0] or create new[1]?\n");
	switch (getchar()) {
		case '0':
			printf("Name: ");
			char buff[16];
			scanf("%15s", buff);
			loadEntities(buff, &pl);
			break;
		default:
			fprintf(stderr, "Invalid option, new game\n");
		case '1':
			newBox(random() % 5, random() % 5);
			newBox(random() % 5, random() % 5);
			addEntity((entity) {{random() % 5, random() % 5}, 'O', false});
			break;
	}
	enum Movement mov = NONE;
	int times = 0;
	char buff[32] = "";
	char str[16] = "", arg[7] = "";
	printBoard();
	afterscanf();
	while (running) {
input:
		printf("> ");
		if(fgets(buff, 32, stdin) == NULL) {
			fprintf(stderr, "No input\n");
			goto input;
		}
		sscanf(buff, "%15s %d", str, &times);
		if ((mov = strToMov(str)) == NONE) {
			puts("Invalid option");
			goto input;
		}
		if(times < 1)
			times = 1;
		else if(times > TIMES_MAX)
			times = TIMES_MAX;
		for(int i = 0; i < times; i++) {
			move(&pl, mov);
		}
		strcpy(str, "");
		strcpy(arg, "");
		times = 1;
		printBoard();
	}
	return EXIT_SUCCESS;
}
void printBoard() {
	for(int i = 0; i<B_WID+1;i++)
		printf("-");
	puts("");
	bool plSeen = false;
	for(int y = 0; y < B_HEI; y++) {
		printf("|");
		for (int x = 0; x < B_WID-1; x++) {
				printf("%c", iconAtPos((pos){y,x}));
		}
		printf("|\n");
	}
	for(int i = 0; i<B_WID+1;i++)
		printf("-");
	puts("");
}