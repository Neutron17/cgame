#include "entity.h"
#include <stdio.h>
#include <string.h>
#include "arr.h"
#include "config.h"
#include "position.h"

entity *entities = NULL;
size_t ent_sz = 0;
size_t  entMax = 0;
entity *pl;

void __defFn() {  }
void setUpEntity(size_t n, entity *player) {
	pl = player;
	if((entities = acalloc(sizeof(entity), n)) == NULL) {
		fprintf(stderr, "Couldn't allocate entities\n");
		exit(1);
	}
	entMax = (int)n;
	for(int i = 0; i < n; i++) {
		entities[i].icon = '?';
	}
}
// is position in entities
bool pinents(pos p) {
	if(pSame(pl->position, p))
		return true;
	for(int i = 0; i < ent_sz; i++) {
		if(pSame(entities[i].position, p))
			return true;
	}
	return false;
}
unsigned addEntity(entity ent) {
	if(ent_sz != entMax) {
		entities[ent_sz] = ent;
		ent_sz++;
	}
	return ent_sz - 1;
}
char iconAtPos(pos p) {
	if(!pinents(p))
		return ' ';
	if(pSame(pl->position, p))
		return pl->icon;
	for(int i = 0; i < ent_sz; i++) {
		//printf("\ni %d y %d x %d\ny %d x %d\n", i, entities[i].position.y, entities[i].position.x, p.y,p.x);
		if(pSame(entities[i].position, p))
			return entities[i].icon;
	}
	return '?';
}
entity *entAtIndex(unsigned index) {
	return &entities[index];
}
// Serialization
void saveEntities(const char *name) {
	char fname[32];
	strcpy(fname, saveDir);
	strcat(fname, name);
	FILE *file = fopen(fname, "wb");
	if(!file) {
		fprintf(stderr, "Couldn't open file: %s\n", name);
		return;
	}
	fwrite(&ent_sz, 1, sizeof(unsigned), file);
	fwrite(pl, 1, sizeof(entity), file);
	for(int i = 0; i<ent_sz;i++)
		fwrite(&entities[i], 1, sizeof(entity), file);
	fclose(file);
}
void loadEntities(const char *name, entity *player) {
	char fname[32];
	strcpy(fname, saveDir);
	strcat(fname, name);
	FILE *file = fopen(fname, "rb");
	if (!file) {
		fprintf(stderr, "Couldn't open file: %s\n", fname);
		return;
	}
	unsigned sz;
	fread(&sz, 1, sizeof(unsigned), file);
	ent_sz = sz;
	fread(player, 1, sizeof(entity), file);
	for (int i = 0; i < ent_sz; i++)
		fread(&entities[i], 1, sizeof(entity), file);
	fclose(file);
}

void printEnts() {
	for(int i = 0; i<ent_sz;i++) {
		printf("%c", entities[i].icon);
	}
}
