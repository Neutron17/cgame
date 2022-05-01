//
// Created by neutron17 on 2022.04.22..
//

#include "collider.h"
#include <stdio.h>

void (*const HandlerLUT[])(entity rec, entity coller, enum Movement side) = {
		__defFn, boxCollHandler
};

void collHandler(enum CollType coll, entity rec, entity coller, enum Movement side) {
	HandlerLUT[coll](rec, coller, side);
}

void boxCollHandler(entity rec, entity coller, enum Movement side) {
	printf("Collided %d %d\n", rec.position.x, rec.position.y);
}