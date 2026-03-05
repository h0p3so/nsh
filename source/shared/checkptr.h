#ifndef NSH_SHARED_CHECKPTR_H
#define NSH_SHARED_CHECKPTR_H

#include "meta.h"

#include <stdio.h>
#include <stdlib.h>

#define NSH_SHARED_CHECKPTR(p, s, m) do {          \
	if (p) { break; }                          \
	fprintf(                                   \
		stderr,                            \
		"%s:%s (%s:%d): failed at `%s`\n", \
		NSH_SHARED_META_NAME,              \
		s,                                 \
		__FILE__,                          \
		__LINE__,                          \
		m                                  \
	);                                         \
	abort();                                   \
} while (0)

#endif
