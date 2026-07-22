#ifndef NSH_COMMON_BUILTINTYPES_H
#define NSH_COMMON_BUILTINTYPES_H

#include "lextypes.h"

typedef void (*builtin_run_t) (const struct LexToken*, const struct LexToken*);

struct BuiltInCmd
{
	const char *name;
	const char *help;
	const size_t length;
	const builtin_run_t run;
};

#endif
