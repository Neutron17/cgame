#ifndef _NTR_ENTITY_H_
#define _NTR_ENTITY_H_
#include <stdbool.h>
#include <stdlib.h>
#include "position.h"
#include "optarg.h"
#include "collType.h"

void __defFn();

typedef struct entity {
	pos  position;
	char icon;
	bool doCollide;
	enum CollType collisionType;
} entity;


#define _entity2(pos, icon) (entity) { pos, icon, true, DEF }
#define _entity3(pos, icon, collide) (entity) { pos, icon, collide, DEF }
#define _entity4(pos, icon, collide, ctp) (entity) { pos, icon, collide, ctp }
#define Entity(...) __CONC(_entity, __NARGS(__VA_ARGS__))(__VA_ARGS__)

extern size_t ent_sz;

void setUpEntity(size_t n, entity *player);
// Returns: index
unsigned addEntity(entity ent);
char iconAtPos(pos p);
entity *entAtIndex(unsigned index);
void printEnts();
void saveEntities(const char *name, entity  pl);
void loadEntities(const char *name, entity *pl);

#endif //_NTR_ENTITY_H_
