#ifndef _NTR_MOVEMENT_H_
#define _NTR_MOVEMENT_H_ 1

#include "entity/entity.h"

#define B_WID 6
#define B_HEI 5

enum Movement {
	QUIT, NONE,
	UP, DOWN, LEFT, RIGHT,
	SAVE, LOAD, RESTART
};
#define MOV_SZ 9
struct sermov {
	bool multiple;	// ref: names quit: true
	int lens[2];	// quit: { 4(quit), 4(exit) }
	char *names;	// quit: quitexit
	char *chnames;	// up: wu
	enum Movement type;
};

enum Movement strToMov(const char *in);
void move(entity *pl, enum Movement mov/*, const char *arg*/);

#endif//_NTR_MOVEMENT_H_
