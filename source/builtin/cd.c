/*
 * cd built-in
 *
 * Changes the current directory. Supports ~ as an
 * alias for the user's home directory.
 */

#include "cd.h"
#include "pwd.h"
#include "comm.h"
#include "../libs/stdv.h"
#include "../path.h"

#include <unistd.h>
#include <errno.h>
#include <stdio.h>

void builtin_cd_cmd_run (const struct ParserTreeCmd *treeCmd)
{
	const size_t argc = stdv_size(treeCmd->commandRelated.argv);
	struct PathPath resolved = path_resolve(
		argc == NSH_BUILTIN_COMM_ARG_OFF ?
		"~"                              : // TODO
		stdv_get(treeCmd->commandRelated.argv, NSH_BUILTIN_COMM_ARG_OFF)
	);

	if (chdir(resolved.path) == 0)
	{
		builtin_pwd_update(&resolved);
		return;
	}

	switch (errno)
	{
		case ENOENT:
		{
			printf("cd: %s: No such file or directory\n", resolved.path);
			return;
		}
	}
}
