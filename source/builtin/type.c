#include "type.h"
#include "../builtin.h"
#include "libs/stdv.h"

#include <stdio.h>

void builtin_type_cmd_run (const struct ParserTreeCmd *treeCmd)
{
	if (stdv_size(treeCmd->commandRelated.argv) == 0)
	{ return; }

	const char *cmdname = stdv_get(treeCmd->commandRelated.argv, 0);
	const struct BuiltInCmd *isbuiltin = builtin_get(cmdname);

	if (isbuiltin)
	{ printf("%s is a shell builtin\n", cmdname); return; }

	printf("%s: not found\n", cmdname);
}
