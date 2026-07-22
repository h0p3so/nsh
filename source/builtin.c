#include "builtin.h"

#include "builtin/exit.h"
#include "builtin/echo.h"

#include <string.h>
#include <stdlib.h>

#define NSH_BUILTIN_BUILTIN_COUNT 2

static int32_t _cmp (const void *p, const void *q)
{
	const char *name1 = ((struct BuiltInCmd*) p)->name;
	const char *name2 = ((struct BuiltInCmd*) q)->name;

	return strcmp(name1, name2);
}

static int32_t _search (const void *p, const void *q)
{
	struct BuiltInCmd *d = (struct BuiltInCmd*) p;
	struct BuiltInCmd *b = (struct BuiltInCmd*) q;

	return strncmp(d->name, b->name, d->length);
}


static const struct BuiltInCmd *_get_all (void)
{
	static bool initd = false;
	static struct BuiltInCmd cmds[NSH_BUILTIN_BUILTIN_COUNT] = {
		{ .name = "exit", .length = 4, .run = exit_builtin_run },
		{ .name = "echo", .length = 4, .run = echo_builtin_run }
	};

	if (!initd)
	{
		qsort(cmds, NSH_BUILTIN_BUILTIN_COUNT, sizeof(cmds[0]), _cmp);
		initd = true;
	}
	return cmds;
}

const struct BuiltInCmd *builtin_get (const char *name, const size_t length)
{
	const struct BuiltInCmd *cmds = _get_all();
	struct BuiltInCmd filter =
	{ .name = name, .length = length };

	return (struct BuiltInCmd*) bsearch(
		&filter, cmds, NSH_BUILTIN_BUILTIN_COUNT, sizeof(cmds[0]), _search
	);
}
