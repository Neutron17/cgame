//
// Created by neutron17 on 2022.05.03..
//

#include "common.h"
#include <stdio.h>

void afterscanf() {
	int c;
	do {
		c = getchar();
	} while (c != EOF && c != '\n');
}