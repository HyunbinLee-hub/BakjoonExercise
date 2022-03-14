#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(void)
{
	char *fname = "ssu_text.txt";
	int fd;

	if ((fd = open(fname, O_RDONLY)) < 0) {
		fprintf(stderr, "open error for %s\n", fname);
		exit(1);
	}
	else {
		printf("Success!\nFilename : %s\nDescriptor : %d\n", fname, fd);
	}

	exit(0);
}
