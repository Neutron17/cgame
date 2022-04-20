#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "arr.h"
#include "board.h"
#include "position.h"
#include "entity.h"

#define INP_SZ 16

bool isDebug = true;

void printBoard();
enum Movement strToMov(const char *in);
void move(entity *pl, pos box, enum Movement mov);
bool moveBlocked(pos plPos, pos box, enum Movement mov);


bool running = true;

#define PL_ICON 'X'
#define BX_ICON 'W'

int main(int argc, const char *argv[]) {
    entity pl = { { 2,2 }, PL_ICON };
    setUpEntity(9, &pl);
    //addEntity((entity){ { 2,3 }, PL_ICON });
    addEntity((entity) { {rand()%5, rand()%5} , BX_ICON});
    addEntity((entity) { {rand()%5, rand()%5} , BX_ICON});
    char inp[INP_SZ];
    enum Movement mov = NONE;
    printBoard();
    while(running) {
        printf("> ");
        scanf("%15s", inp);
        mov = strToMov(inp);
        printf("%s %d\n", inp, mov);
        move(&pl,(pos){0,0},mov);
        printBoard();
    }
    return EXIT_SUCCESS;
}
void move(entity *pl, pos box, enum Movement mov) {
    for(int i = 0; i < ent_sz; i++) {
        if (moveBlocked(pl->position, entAtIndex(i)->position, mov)) {
            puts("Blocked");
            return;
        }

        puts("not blocked");
    }
        switch (mov) {
            case QUIT:
                if (isDebug)
                    puts("Exiting...");
                running = false;
                return;
            case UP:
                if (isDebug)
                    puts("U");
                if (pl->position.y > 0)
                    pl->position.y--;
                break;
            case DOWN:
                if (isDebug)
                    puts("D");
                if (pl->position.y + 1 < B_HEI)
                    pl->position.y++;
                break;
            case LEFT:
                if (isDebug)
                    puts("L");
                if (pl->position.x > 0)
                    pl->position.x--;
                break;
            case RIGHT:
                if (isDebug)
                    puts("R");
                if (pl->position.x + 1 < B_WID - 1)
                    pl->position.x++;
                break;
            case NONE:
                fprintf(stderr, "Command not found\n");
                if (isDebug)
                    puts("NONE");
                fflush(stderr);
                break;
            default:
                break;
        }
}

bool moveBlocked(pos plPos, pos boxPos, enum Movement mov) {
    pos diff = pDiff(plPos, boxPos);
    printf("diff: x %d y %d\npl x %d y %d\n"
           "box x %d y %d\n",
           diff.x, diff.y, plPos.x, plPos.y,
           boxPos.x,boxPos.y);
    if(pSumU(diff) != 1)
        return false;
    if(mov == UP || mov == DOWN) {
        if(diff.y == 0)
            return false;
        if(mov == UP) {
            if(diff.y == 1)
                return true;
        } else {
            if(diff.y == -1)
                return true;
        }
    } else if(mov == LEFT || mov == RIGHT) {
        if(diff.x == 0)
            return false;
        if(mov == RIGHT) {
            if(diff.x == -1)
                return true;
        } else {
            if(diff.x == 1)
                return true;
        }
    }
    return false;
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
                printf("%c", iconAtPos((pos){y,x}));
        }
        printf("|\n");
    }
    for(int i = 0; i<B_WID+1;i++)
        printf("-");
    puts("");
}

/* WARNING: Do not call alloc, allocArr_add, ect.
 * Reason: allocArr_ctor not called yet             */
__attribute__((used)) __attribute__((constructor)) void startUp() {
    srand(time(NULL));
    //while(pSum(pDiff(plPos, boxPos)) != 0)
    //    boxPos = (pos){ rand() % 5, rand() % 5 };
    //board[boxPos.y][boxPos.x] = BX_ICON;
}