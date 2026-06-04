/*
 * exit built-in
 *
 * Exits the shell with an optional status code.
 * If no argument is given, exits with 0.
 */

#ifndef NSH_BUILTIN_EXIT_H
#define NSH_BUILTIN_EXIT_H

#include "shared/builtintypes.h"

void builtin_exit_cmd_run (const struct ParserTreeCmd*);

static const struct BuiltInCmd GLOB_BUILTIN_EXIT_CMD_META =
{
	.name = "exit",
	.help = "exits the shell",
	.run = builtin_exit_cmd_run
};

#endif
