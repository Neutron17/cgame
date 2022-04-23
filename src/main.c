#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "arr.h"
#include "board.h"
#include "position.h"
#include "entity.h"
#include "collider.h"

#define INP_SZ 16

bool isDebug = true;

void printBoard();
enum Movement strToMov(const char *in);
void move(entity *pl, enum Movement mov);
bool moveBlocked(entity pl, entity box, enum Movement mov);
void saveEntities(const char *name, entity  pl);
void loadEntities(const char *name, entity *pl);

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
    char inp[INP_SZ];
    enum Movement mov = NONE;
    printBoard();
    while(running) {
        inp:
        printf("> ");
        scanf("%15s", inp);
        if((mov = strToMov(inp)) == NONE) {
            puts("Invalid option");
            goto inp;
        }
        printf("%s %d\n", inp, mov);
        move(&pl, mov);
        printBoard();
    }
    return EXIT_SUCCESS;
}
void move(entity *pl, enum Movement mov) {
    for (int i = 0; i < ent_sz; i++) {
        if (!entAtIndex(i)->doCollide)
            continue;
        if (moveBlocked(*pl, *entAtIndex(i), mov))
            return;
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
        case SAVE:
            printf("Filename: ");
            char buff[16];
            scanf("%15s", buff);
            saveEntities(buff, *pl);
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

bool moveBlocked(entity pl, entity box, enum Movement mov) {
    pos boxPos = box.position;
    pos plPos = pl.position;
    pos diff = pDiff(plPos, boxPos);
    printf("diff: x %d y %d\npl x %d y %d\n"
           "box x %d y %d\n",
           diff.x, diff.y, plPos.x, plPos.y,
           boxPos.x,boxPos.y);
    if(pSumU(diff) != 1)
        goto f;
    if(mov == UP || mov == DOWN) {
        if(diff.y == 0)
            goto f;
        if(mov == UP) {
            if(diff.y == 1)
                goto t;
        } else {
            if(diff.y == -1)
                goto t;
        }
    } else if(mov == LEFT || mov == RIGHT) {
        if (diff.x == 0)
            goto f;
        if (mov == RIGHT) {
            if (diff.x == -1)
                goto t;
        } else {
            if (diff.x == 1)
                goto t;
        }
    }
f:
    return false;
t:
    collHandler(box.collisionType, box, pl, mov);
    return true;
}

void saveEntities(const char *name, entity  pl) {
    FILE *file = fopen(name, "wb");
    if(!file) {
        fprintf(stderr, "Couldn't open file: %s\n", name);
        return;
    }
    fwrite(&ent_sz, 1, sizeof(unsigned), file);
    fwrite(&pl, 1, sizeof(entity), file);
    for(int i = 0; i<ent_sz;i++) {
        fwrite(&entities[i], 1, sizeof(entity), file);
    }
    /*for(int i = 0; i < ent_sz; i++) {
        fwrite(*entAtIndex(i), 1)
    }*/
    fclose(file);
}
void loadEntities(const char *name, entity *pl) {
    FILE *file = fopen(name, "rb");
    if (!file) {
        fprintf(stderr, "Couldn't open file: %s\n", name);
        return;
    }
    unsigned sz;
    fread(&sz, 1, sizeof(unsigned), file);
    ent_sz = sz;
    fwrite(pl, 1, sizeof(entity), file);
    for (int i = 0; i < ent_sz; i++) {
        fread(&entities[i], 1, sizeof(entity), file);
        //printf("%d %d %c\n", entities[i].position.x, entities[i].position.y, entities[i].icon);
    }
    fclose(file);
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
    } else if(strncasecmp(in, "save", 4) == 0) {
        return SAVE;
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
}