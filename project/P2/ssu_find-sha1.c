#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <openssl/sha.h>
#include "ssu_functions.h"

int d_option, i_option, f_option, t_option;

int main(int argc, char *argv[])
{
	struct timeval begin_t, end_t;

	if (argc != ARGMAX) {
		fprintf(stderr, "usage: %s [FILE_EXTENSION] [MIN_SIZE] [MAXSIZE] [TARGET_DIRECTORY]\n", argv[0]);
		exit(1);
	}
	gettimeofday(&begin_t, NULL);

	gettimeofday(&end_t, NULL);
	ssu_searchTime(&begin_t, &end_t);

	while (1) {
		char cmd[BUFMAX];
		int setIdx;
		int listIdx;
		int count;
		char *token[3];

		printf(">> ");
		fgets(cmd, BUFMAX, stdin);
		cmd[strlen(cmd)-1] = '\0';
		if ((count = parseCmd(cmd, token)) == 0) {
			continue;
		}

		if (strcmp(token[0], "exit") == 0) {
			printf(">> Back to Prompt\n");
			break;
		}

		if (atoi(token[0]) < 0) {
			fprintf(stderr, "set index error\n");
			continue;
		}

		setIdx = atoi(token[0]);

		if (strcmp(token[1], "d") == 0) {
			if (atoi(token[2]) < 0) {
				fprintf(stderr, "list index error\n");
				continue;
			}
		}
		else if (strcmp(token[1], "i") == 0) {
		}
		else if (strcmp(token[1], "f") == 0) {
		}
		else if (strcmp(token[1], "t") == 0) {
		}
		else {
			fprintf(stderr, "option error\n");
		}

		d_option = i_option = f_option = t_option = FALSE;
	}

	exit(0);
}
