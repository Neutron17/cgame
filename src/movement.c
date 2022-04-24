#include "movement.h"
#include "collider.h"

extern const bool isDebug;
extern bool running;

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

void move(entity *pl, enum Movement mov, const char *arg) {
    printf("%p\n", arg);
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
        case SAVE: {
            printf("Name: ");
            char buff[16];
            scanf("%15s", buff);
            saveEntities(buff, *pl);
            break;
	}
	case LOAD:{
            printf("Name: ");
            char buff[16];
            scanf("%15s", buff);
            loadEntities(buff, pl);
	    break;
	}
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
    } else if(strncasecmp(in, "load", 4) == 0) {
	return LOAD;
    } else {
        return NONE;
    }
}
