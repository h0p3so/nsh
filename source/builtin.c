#include "builtin.h"
#include "builtin/exit.h"

#include <stdlib.h>
#include <string.h>

#define _BUILTIN_COUNT 1

static const struct BuiltInCmd *_builtin_get_all (void);
static int32_t _builtin_sort (const void*, const void*);

const struct BuiltInCmd *builtin_get (const char *cmdname)
{
	const struct BuiltInCmd *cmds = _builtin_get_all();

	struct BuiltInCmd key =
	{ .name = cmdname };

	return (struct BuiltInCmd*) bsearch(
		&key, cmds, _BUILTIN_COUNT, sizeof(cmds[0]), _builtin_sort
	);
}

static const struct BuiltInCmd *_builtin_get_all (void)
{
	static bool set = false;
	static struct BuiltInCmd cmds[_BUILTIN_COUNT] = {
		GLOB_BUILTIN_EXIT_CMD_META,
	};

	if (!set)
	{
		qsort(cmds, _BUILTIN_COUNT, sizeof(cmds[0]), _builtin_sort);
		set = true;
	}
	return cmds;
}

static int32_t _builtin_sort (const void *p, const void *q)
{
	const char *name1 = ((struct BuiltInCmd*) p)->name;
	const char *name2 = ((struct BuiltInCmd*) q)->name;
	return strcmp(name1, name2);
}

