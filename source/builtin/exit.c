#include "builtin.h"
#include "libs/stdv.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define _EXIT_FAILRE -1
#define _EXIT_OK      0
#define _EXIT_MOD     255

static int32_t _exit_get_argument (const struct ParserTreeCmd*);

void builtin_exit_cmd_run (const struct ParserTreeCmd *treeCmd)
{
	int32_t status = _exit_get_argument(treeCmd);

	printf("exiting with %d status. Goodbye..\n", status);
	exit(status % _EXIT_MOD);
}

static int32_t _exit_get_argument (const struct ParserTreeCmd *treeCmd)
{
	if (stdv_size(treeCmd->commandRelated.argv) == 0)
	{ return _EXIT_OK; }

	const char *argument = stdv_get(treeCmd->commandRelated.argv, 0);

	if (isdigit(*argument))
	{ return (int32_t) atoi(argument); }

	return _EXIT_FAILRE;
}
