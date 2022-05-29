#include "editor.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../error.h"
#include "../common.h"

void editor(void) {
	puts("Welcome to the Editor");
	puts("Options:\n"
		 "\tq: exit\n"
		 "\ts <arg>: select file");
	bool running = true;
	while(running) {
		input:;
		char buff[32];
		if (fgets(buff, 32, stdin) == NULL) {
			fprintf(stderr, "No input\n");
			goto input;
		}
		char *cmd = strtok(buff, " ");
		char *arg = strtok(NULL, " ");
		switch (cmd[0]) {
			case 'q':
				running = false;
				break;
			case 's':
				if(!file_exists(arg)) {
					fprintf(stderr, "File does not exits\n");
					break;
				}
				break;
			default:
				fprintf(stderr, "Invalid option\n");
				break;
		}
	}
}