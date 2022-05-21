#ifndef _NTR_MOVEMENT_H_
#define _NTR_MOVEMENT_H_ 1

#include "entity.h"

#define B_WID 1200/50
#define B_HEI 700/50

enum Movement {
	QUIT, NONE,
	UP, DOWN, LEFT, RIGHT,
	SAVE, LOAD, RESTART
};
#define MOV_SZ 8
struct sermov {
	bool multiple;	// ref: names quit: true
	int lens[2];	// quit: { 4(quit), 4(exit) }
	char *names;	// quit: quitexit
	char *chnames;	// up: wu
	enum Movement type;
};

enum Movement strToMov(const char *in);
void move(entity *pl, enum Movement mov/*, const char *arg*/);
pos unusedPos(void);

#endif//_NTR_MOVEMENT_H_
