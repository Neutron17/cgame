//
// Created by neutron17 on 2022.04.22..
//

#include "collider.h"
#include <stdio.h>

void boxCollHandler(entity rec, entity coller, enum Movement side) {
    printf("Collided %d %d\n", rec.position.x, rec.position.y);
}