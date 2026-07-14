#ifndef NSH_BUILTIN_PWD_H
#define NSH_BUILTIN_PWD_H

#include "shared/builtintypes.h"

void builtin_pwd_set_origin (void);
void builtin_pwd_go_home (void);
void builtin_pwd_aux_add (const char*, const size_t);

void builtin_pwd_cmd_run (const struct ParserTreeCmd*);
static const struct BuiltInCmd GLOB_BUILTIN_PWD_CMD_META =
{
	.name = "pwd",
	.help = "print working dir",
	.run = builtin_pwd_cmd_run
};

void builtin_pwd_clean (void);

#endif
