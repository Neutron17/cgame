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

const bool isDebug = true;
bool running = true;

void printBoard();

#define PL_ICON 'X'
#define BX_ICON 'W'
#define newBox(x,y) addEntity((entity) { { x, y }, BX_ICON, true, BOX})

int main(int argc, const char *argv[]) {
	srand(time(NULL));
	saveDir = alloc(32);
	strcpy(saveDir, "saves/");
	printf("config: %s\n", saveDir);
	entity pl = Entity(((pos) {1, 2}), PL_ICON, false, DEF);
	setUpEntity(9, &pl);
	printf("Load[0] or create new[1]?\n");
	switch (getchar()) {
		case '0':
			printf("Name: ");
			char buff[16];
			scanf("%15s", buff);
			loadEntities(buff, &pl);
			updatePl(&pl);
			break;
		default:
			fprintf(stderr, "Invalid option, new game\n");
		case '1':
			newBox(rand() % 5, rand() % 5);
			newBox(rand() % 5, rand() % 5);
			addEntity((entity) {{rand() % 5, rand() % 5}, 'O', false});
			break;
	}
	enum Movement mov = NONE;
	int count = 0, times = 0;
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
		count = sscanf(buff, "%15s %d", str, &times);
		if ((mov = strToMov(str)) == NONE) {
			puts("Invalid option");
			goto input;
		}
		if (count == 1 || times < 1) {
			move(&pl, mov);
		} else {
			for (int i = 0; i < times; i++) {
				move(&pl, mov);
			}
		}
		strcpy(str, "");
		strcpy(arg, "");
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