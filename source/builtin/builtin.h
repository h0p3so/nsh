#ifndef NSH_BUILTIN_BUILTIN_H
#define NSH_BUILTIN_BUILTIN_H

#include "../common/lextypes.h"

typedef void (*builtin_run_t) (const struct LexToken*, const struct LexToken*);

struct BuiltInCmd
{
	const char *name;
	const char *help;
	const size_t length;
	const builtin_run_t run;
};

const struct BuiltInCmd *builtin_get (const char*, const size_t);

#endif
