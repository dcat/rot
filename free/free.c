#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>


void
usage(char *name) {
	fprintf(stderr, "usage: %s [-m | -k | -g]\n", name);
	exit(0);
}

int
main(int argc, char **argv) {
	long pg, pgsiz, avphys;
	int mod = 10;
	char suf = ' ';

	if (argc > 1) {
		if (argv[1][0] == '-') {
			switch (argv[1][1]) {
			case 'm':
				mod = 20;
				suf = 'M';
				break;
			case 'g':
				mod = 30;
				suf = 'G';
				break;
			}
		}
	}

	if ((pg = sysconf(_SC_PHYS_PAGES)) < 0)
		err(1, "sysconf");

	if ((pgsiz = sysconf(_SC_PAGE_SIZE)) < 0)
		err(1, "sysconf");

	if ((avphys = sysconf(_SC_AVPHYS_PAGES)) < 0)
		err(1, "sysconf");

	printf("%*s%*s%*s\n",
			16, "total",
			11, "used",
			11, "free"
	);

	printf("Mem:%*ld%c%*ld%c%*ld%c\n",
			12, pg * pgsiz >> mod, suf,
			11, (pg - avphys) * pgsiz >> mod, suf,
			11, avphys * pgsiz >> mod, suf
	);

	return 0;
}
