//
// Created by neutron17 on 2022.04.22..
//

#ifndef _NTR_COLLIDER_H_
#define _NTR_COLLIDER_H_ 1

#include "entity.h"
#include "movement.h"

void collHandler(enum CollType coll, entity rec, entity *coller, enum Movement side);
void boxCollHandler(entity rec, entity *coller, enum Movement side);
void endCollHandler(entity rec, entity *coller, enum Movement side);

#endif //_NTR_COLLIDER_H_
