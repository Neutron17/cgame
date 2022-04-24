#ifndef _NTR_MOVEMENT_H_
#define _NTR_MOVEMENT_H_ 1

#include "entity.h"

#define B_WID 6
#define B_HEI 5

enum Movement {
    QUIT, NONE,
    UP, DOWN, LEFT, RIGHT,
    SAVE, LOAD
};
enum Movement strToMov(const char *in);
void move(entity *pl, enum Movement mov, const char *arg);

#endif//_NTR_MOVEMENT_H_
