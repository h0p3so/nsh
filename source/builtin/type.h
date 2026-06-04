/*
 * type built-in
 *
 * Reports whether a command is a built-in or an
 * external executable, and where it is found.
 */

#ifndef NSH_BUILTIN_TYPE_H
#define NSH_BUILTIN_TYPE_H

#include "shared/builtintypes.h"

void builtin_type_cmd_run (const struct ParserTreeCmd*);

static const struct BuiltInCmd GLOB_BUILTIN_TYPE_CMD_META =
{
	.name = "type",
	.help = "what type is this?",
	.run = builtin_type_cmd_run
};

#endif
