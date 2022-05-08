//
// Created by neutron17 on 2022.04.22..
//

#include "collider.h"
#include <stdio.h>

extern const bool isDebug;

void (*const HandlerLUT[])(entity rec, entity *coller, enum Movement side) = {
		__defFn, boxCollHandler, endCollHandler
};

void collHandler(enum CollType coll, entity rec, entity *coller, enum Movement side) {
	HandlerLUT[coll](rec, coller, side);
}

void boxCollHandler(entity rec, entity *coller, enum Movement side) {
	if(isDebug)
		printf("Collided %d %d\n", rec.position.x, rec.position.y);
}
void endCollHandler(entity rec, entity *coller, enum Movement side) {
	puts("Next Level");
	fflush(stdout);
	move(coller, RESTART);
}