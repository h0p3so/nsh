/*
 * pwd built-in
 *
 * Tracks the current working directory and provides
 * helpers for cd to build paths incrementally.
 */

#ifndef NSH_BUILTIN_PWD_H
#define NSH_BUILTIN_PWD_H

#include "shared/builtintypes.h"
#include "shared/pathinfo.h"

void builtin_pwd_cmd_run (const struct ParserTreeCmd*);
const struct PathPath *builtin_pwd_get_cwd (void);
void builtin_pwd_update (const struct PathPath*);

static const struct BuiltInCmd GLOB_BUILTIN_PWD_CMD_META =
{
	.name = "pwd",
	.help = "print working dir",
	.run = builtin_pwd_cmd_run
};

#endif
