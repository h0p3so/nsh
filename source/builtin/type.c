/*
 * type built-in
 *
 * Reports whether a command is a built-in or an
 * external executable, and where it is found.
 */

#include "type.h"
#include "comm.h"
#include "../builtin.h"
#include "libs/stdv.h"
#include "../ext.h"

#include <stdio.h>

void builtin_type_cmd_run (const struct ParserTreeCmd *treeCmd)
{
	if (stdv_size(treeCmd->commandRelated.argv) == NSH_BUILTIN_COMM_ARG_OFF)
	{ return; }

	const char *cmdname = stdv_get(treeCmd->commandRelated.argv, NSH_BUILTIN_COMM_ARG_OFF);
	const struct BuiltInCmd *isbuiltin = builtin_get(cmdname);

	if (isbuiltin)
	{ printf("%s is a shell builtin\n", cmdname); return; }

	ext_path_t epath = {0};
	const bool isexternal = ext_is_command_external(cmdname, &epath);

	if (isexternal)
	{ printf("%s is %s\n", cmdname, epath); return; }

	printf("%s: not found\n", cmdname);
}
