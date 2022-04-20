//
// Created by neutron17 on 2022.04.18..
//

#ifndef _NTR_ENTITY_H_
#define _NTR_ENTITY_H_
#include <stdbool.h>
#include <stdlib.h>
#include "board.h"
#include "position.h"

typedef struct {
    pos  position;
    char icon;
} entity;
extern size_t ent_sz;

void setUpEntity(size_t n, entity *player);
// is position in entities
bool pinents(pos p);
// Returns: index
unsigned addEntity(entity ent);
char iconAtPos(pos p);
entity *entAtIndex(unsigned index);
void printEnts();

#endif //_NTR_ENTITY_H_