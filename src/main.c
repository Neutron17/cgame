#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "arr.h"
#include "board.h"

#define INP_SZ 16

bool isDebug = true;

void printBoard();
enum Movement strToMov(const char *in);
void move(enum Movement mov);

bool running = true;

#define PL_ICON 'X'
#define BX_ICON 'O'
pos plPos  = { 0, 0 };
pos boxPos = { 0, 0 };

__attribute__((used))  __attribute__((constructor)) void startUp() {
    srand(time(NULL));
    plPos  = (pos){ rand() % 5, rand() % 5 };
    while(boxPos.x != plPos.x && boxPos.y != plPos.y)
        boxPos = (pos){ rand() % 5, rand() % 5 };
    board[boxPos.y][boxPos.x] = BX_ICON;
    if(isDebug)
        printf("Box: y: %d x: %d\n", boxPos.y, boxPos.x);
}

int main(int argc, const char *argv[]) {
    char inp[INP_SZ];
    enum Movement mov = NONE;
    printBoard();
    while(running) {
        printf("> ");
        scanf("%15s", inp);
        mov = strToMov(inp);
        printf("%s %d\n", inp, mov);
        move(mov);
        printBoard();
    }
	return EXIT_SUCCESS;
}
void move(enum Movement mov) {
    switch(mov) {
        case QUIT:
            if(isDebug)
                puts("Exiting...");
            running = true;
        case UP:
            if(isDebug)
                puts("U");
            if(plPos.y > 0)
                plPos.y--;
            break;
        case DOWN:
            if(isDebug)
                puts("D");
            if(plPos.y+1 < B_HEI)
                plPos.y++;
            break;
        case LEFT:
            if(isDebug)
                puts("L");
            if(plPos.x > 0)
                plPos.x--;
            break;
        case RIGHT:
            if(isDebug)
                puts("R");
            if(plPos.x+1 < B_WID-1)
                plPos.x++;
            break;
        case NONE:
            fprintf(stderr, "Command not found\n");
            if(isDebug)
                puts("NONE");
            fflush(stderr);
            break;
        default: break;
    }
}

enum Movement strToMov(const char *in) {
    if(strnlen(in, 2) == 1) {
        switch (in[0]) {
            case 'q': return QUIT;
            case 'w': return UP;
            case 'a': return LEFT;
            case 's': return DOWN;
            case 'd': return RIGHT;

            case 'u': return UP;
            case 'l': return LEFT;
            case 'r': return RIGHT;
            default : break;
        }
    }
    if(strncasecmp(in, "quit", 4) == 0 || strncasecmp(in, "exit", 4) == 0) {
        return QUIT;
    } else if(strncasecmp(in, "up", 2) == 0) {
        return UP;
    } else if(strncasecmp(in, "down", 4) == 0) {
        return DOWN;
    } else if(strncasecmp(in, "left", 4) == 0) {
        return LEFT;
    } else if(strncasecmp(in, "right", 5) == 0) {
        return RIGHT;
    } else {
        return NONE;
    }
}

void printBoard() {
    for(int i = 0; i<B_WID+1;i++)
        printf("-");
    puts("");
    bool plSeen = false;
    for(int y = 0; y < B_HEI; y++) {
        printf("|");
        for (int x = 0; x < B_WID-1; x++) {
            if(!plSeen && plPos.x == x && plPos.y == y) {
                plSeen = true;
                printf("%c", PL_ICON);
            } else {
                printf("%c", board[x][y]);
            }
        }
        printf("|\n");
    }
    for(int i = 0; i<B_WID+1;i++)
        printf("-");
    puts("");
}