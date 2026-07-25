#include "libs/stdv.h"
#include "comm.h"
#include "pwd.h"
#include "cd.h"

#include <string.h>

#define _BUILTIN_CD_HOME_ALIAS '~'

// this file only process the argument given to `cd` command, the
// file that actually changes the directory is `pwd`

static void _builtin_cd_home_alias_used (const char*);

void builtin_cd_cmd_run (const struct ParserTreeCmd *treeCmd)
{
	if (stdv_size(treeCmd->commandRelated.argv) == NSH_BUILTIN_COMM_ARG_OFF)
	{ builtin_pwd_go_home(); return; }

	const char *arg = stdv_get(treeCmd->commandRelated.argv, NSH_BUILTIN_COMM_ARG_OFF);

	if (*arg == _BUILTIN_CD_HOME_ALIAS)
	{ _builtin_cd_home_alias_used(arg); return; }


	// TODO: oldpwd
}

static void _builtin_cd_home_alias_used (const char *arg)
{
	const size_t arglen = strlen(arg);
	if (arglen == 1)
	{ builtin_pwd_go_home(); return; }

	for (size_t i = 0; i < arglen; i++)
	{
	}
}
