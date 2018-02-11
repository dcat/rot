#include <unistd.h>
#include <stdio.h>
#include <err.h>


int
main(int argc, char **argv) {
	long pg, pgsiz, avphys;
	int mod = 10;

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

	printf("Mem:%*ld%*ld%*ld\n",
			12, pg * pgsiz >> mod,
			11, (pg - avphys) * pgsiz >> mod,
			11, avphys * pgsiz >> mod
	);

	return 0;
}
