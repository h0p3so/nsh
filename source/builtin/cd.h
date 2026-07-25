#ifndef NSH_BUILTIN_CD_H
#define NSH_BUILTIN_CD_H

#include "shared/builtintypes.h"

void builtin_cd_cmd_run (const struct ParserTreeCmd*);

static const struct BuiltInCmd GLOB_BUILTIN_CD_CMD_META =
{
	.name = "cd",
	.help = "change directory",
	.run = builtin_cd_cmd_run
};

#endif
