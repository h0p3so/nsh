#include "cmd.h"

#include <string.h>
#include <stdlib.h>

static void _exit_call (void)
{
	exit(EXIT_SUCCESS);
}

struct BuiltInCmd
{
	const void (*call) (void);
	const char *name;
	const char *about;
};

static int32_t _builtin_cmd_cmp_fn (const void *cmd1, const void *cmd2)
{
	const char *name1 = ((struct BuiltInCmd*) cmd1)->name;
	const char *name2 = ((struct BuiltInCmd*) cmd2)->name;

	return strcmp(name1, name2);
}

const void* cmd_init_or_get_builtin_cmds (void)
{
	static bool initializated = false;
	static struct BuiltInCmd cmds[NSH_CMD_NUM_BUILT_IN_CMDS] =
	{
		{ .name = "help", .about = "print this message" },
		{ .name = "exit", .about = "exists the shell", .call = _exit_call },
	};

	if (initializated)
	{ return cmds; }

	const size_t membsz = sizeof(cmds[0]);
	qsort(cmds, NSH_CMD_NUM_BUILT_IN_CMDS, membsz, _builtin_cmd_cmp_fn);

	initializated = true;
	return cmds;
}

bool cmd_search_builtin (const char buffer[NSH_COMM_BUFFER_SIZE], const size_t bytes)
{
	const struct BuiltInCmd *cmds = cmd_init_or_get_builtin_cmds();
	struct BuiltInCmd key = {
		.name = buffer
	};

	struct BuiltInCmd *res = bsearch(&key, cmds, NSH_CMD_NUM_BUILT_IN_CMDS, sizeof(cmds[0]), _builtin_cmd_cmp_fn);

	if (res == NULL)
	{ return false; }

	res->call();
	return true;
}

