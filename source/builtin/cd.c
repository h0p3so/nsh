/*
 * cd built-in
 *
 * Changes the current directory. Supports ~ as an
 * alias for the user's home directory.
 */

#include "libs/stdv.h"
#include "../err.h"
#include "comm.h"
#include "pwd.h"
#include "cd.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define _BUILTIN_CD_HOME_ALIAS '~'
#define _BUILTIN_CD_STAGE_NAME "builtin-cd"

static void _builtin_cd_home_alias_used (const char*);
static void _builtin_cd_perform (const char*);

void builtin_cd_cmd_run (const struct ParserTreeCmd *treeCmd)
{
	if (stdv_size(treeCmd->commandRelated.argv) == NSH_BUILTIN_COMM_ARG_OFF)
	{
		_builtin_cd_perform(builtin_pwd_get_home());
		return;
	}

	const char *arg = stdv_get(treeCmd->commandRelated.argv, NSH_BUILTIN_COMM_ARG_OFF);

	if (*arg == _BUILTIN_CD_HOME_ALIAS)
	{ _builtin_cd_home_alias_used(arg); }
	else
	{ builtin_pwd_aux_add(arg, strlen(arg)); builtin_pwd_aux_complete(); }

	_builtin_cd_perform(builtin_pwd_get_cwd());
}

static void _builtin_cd_home_alias_used (const char *arg)
{
	const size_t arglen = strlen(arg);

	/* this handles the single `~`, so it gets
	 * replaced by $HOME value whatever it is
	 */
	const char *homepath = builtin_pwd_get_home();
	const size_t length = strlen(homepath);
	builtin_pwd_aux_add(homepath, length);

	/* in case the argument is either:
	 * ~
	 * or
	 * ~/
	 */
	if (arglen == 1 || arglen == 2)
	{
		builtin_pwd_aux_complete();
		return;
	}

	size_t rawfrom = 2, rawto;
	for (rawto = rawfrom; rawto < arglen; rawto++)
		;;
	
	builtin_pwd_aux_add(arg + rawfrom - 1, rawto - rawfrom + 1);
	builtin_pwd_aux_complete();
}

static void _builtin_cd_perform (const char *resolvedpath)
{
	if (chdir(resolvedpath) == 0)
	{ return; }

	switch (errno)
	{
		case ENOENT:
		{
			printf("cd: %s: No such file or directory\n", resolvedpath);
			return;
		}
	}
	err_fatal(_BUILTIN_CD_STAGE_NAME, "trying to invoke `chdir` syscall");
}
