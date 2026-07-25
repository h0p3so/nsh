/*
 * echo built-in
 *
 * Prints its arguments to stdout, separated by
 * spaces, with a trailing newline.
 */

#ifndef NSH_BUILTIN_ECHO_H
#define NSH_BUILTIN_ECHO_H

#include "shared/builtintypes.h"

void builtin_echo_cmd_run (const struct ParserTreeCmd*);

static const struct BuiltInCmd GLOB_BUILTIN_ECHO_CMD_META =
{
	.name = "echo",
	.help = "echoes stuff",
	.run = builtin_echo_cmd_run
};

#endif
