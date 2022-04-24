#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "arr.h"
#include "movement.h"
#include "position.h"
#include "entity.h"
#include "collider.h"

#define INP_SZ 16

const bool isDebug = true;

struct Input {
	char *str;
	int count;
	int times;
	char *arg;
};

void printBoard();
struct Input input(const char *prompt);

#define newBox(x,y) addEntity((entity) { { x, y }, BX_ICON, true, BOX})

bool running = true;

#define PL_ICON 'X'
#define BX_ICON 'W'

int main(int argc, const char *argv[]) {
    entity pl = Entity(((pos){1,2}), PL_ICON, false, DEF);
    setUpEntity(9, &pl);
    printf("Load[0] or create new[1]?\n");
    switch (getchar()) {
        case '0':
            printf("Filename: ");
            char buff[16];
            //fgets(buff, 15, stdin);
            scanf("%15s", buff);
            loadEntities(buff, &pl);
            updatePl(&pl);
            break;
        default:
            fprintf(stderr, "Invalid option, new game\n");
        case '1':
            newBox(rand()%5,rand()%5);
            newBox(rand()%5,rand()%5);
            addEntity((entity) { {rand()%5,rand()%5}, 'O', false });
            break;
    }
    //loadEntities("foo.dat");
    //char inp[INP_SZ], arg[INP_SZ];
    //int times;
    enum Movement mov = NONE;
    struct Input inp;
    printBoard();
    while(running) {
input:
        //printf("> ");
        //count = scanf("%15s %d", inp, &times);
	inp = input("> ");
	printf("str %s count %d times %d arg %s\n",
		inp.str,inp.count,inp.times,inp.arg);
        if((mov = strToMov(inp.str)) == NONE) {
            puts("Invalid option");
            goto input;
        }
	printf("str %s count %d times %d arg %s\nmov %d\n",
		inp.str,inp.count,inp.times,inp.arg,mov);
	free(inp.str);
	if(inp.count == 1 || inp.times < 1) {
            move(&pl, mov, inp.arg);
	} else {
	    for(int i = 0; i < inp.times; i++) {
		    move(&pl, mov, inp.arg);
	    }
	}
	free(inp.arg);
        printBoard();
    }
    return EXIT_SUCCESS;
}
struct Input input(const char *prompt) {
	char *buff = (char*)malloc(16);
	if(!buff)
		goto allErr;
	printf("%3s", prompt);
	if(fgets(buff, 15, stdin) == NULL)
		__defFn();
	char *str = malloc(7);
	char *arg = malloc(7);
	int times = 0;
	if(!str || !arg)
		goto allErr;
	int count = sscanf(buff, "%6s %d %s", str, &times, arg);
	printf("str %s count %d times %d arg %s\nmov %s\n",
		str,count,times,arg,buff);
	free(buff);
	return (struct Input) { buff, count, times, arg };
allErr:
	fprintf(stderr, "Couldn't allocate memory\n");
	return (struct Input) { NULL, 0, 0, NULL };
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

/* WARNING: Do not call alloc, allocArr_add, ect.
 * Reason:  allocArr_ctor not called yet             */
__attribute__((used)) __attribute__((constructor)) void startUp() {
    srand(time(NULL));
}
