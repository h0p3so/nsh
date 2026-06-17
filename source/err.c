#include "err.h"
#include "shared/meta.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void err_fatal (const char *stage, const char *msg)
{
	int olderrno = errno;
	fprintf(
		stderr,
		"%s [%s]:%s: cannot continue due to system errors\n\terror ocurr while %s\n",
		NSH_SHARED_META_NAME,
		NSH_SHARED_META_VERSION,
		stage,
		msg
	);

	if (olderrno)
	{ fprintf(stderr, "\terror is: %s\n", strerror(olderrno)); }

	fprintf(stderr, "Aborting now!\n");
	exit(EXIT_FAILURE); // TODO: do clean up
}
