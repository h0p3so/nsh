#include "libs/stdv.h"
#include "comm.h"
#include "pwd.h"
#include "cd.h"

#include <string.h>

#define _BUILTIN_CD_HOME_ALIAS '~'

// this file only process the argument given to `cd` command, the
// file that actually changes the directory is `pwd`

void builtin_cd_cmd_run (const struct ParserTreeCmd *treeCmd)
{
	if (stdv_size(treeCmd->commandRelated.argv) == NSH_BUILTIN_COMM_ARG_OFF)
	{ builtin_pwd_go_home(); return; }

	const char *arg = stdv_get(treeCmd->commandRelated.argv, NSH_BUILTIN_COMM_ARG_OFF);
	const size_t arglen = strlen(arg);

	if (*arg == _BUILTIN_CD_HOME_ALIAS && arglen == 1)
	{ builtin_pwd_go_home(); }

	if (*arg == _BUILTIN_CD_HOME_ALIAS && arglen == 2 && arg[1] == '/')
	{ builtin_pwd_go_home(); }


	// TODO: oldpwd
}
