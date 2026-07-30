/*
 * pwd built-in
 *
 * Tracks the current working directory and provides
 * helpers for cd to build paths incrementally.
 */

#include "pwd.h"
#include "shared/pathinfo.h"

#include <stdio.h>
#include <unistd.h>

static struct PathPath _pwd_cwd = {0};

void builtin_pwd_cmd_run (const struct ParserTreeCmd *treeCmd)
{
	(void) treeCmd;

	static bool firstcall = true;
	if (firstcall)
	{
		getcwd(_pwd_cwd.path, NSH_SHARED_PATHINFO_PATH_MAX); // TODO handle
		firstcall = false;
	}
	printf("%s\n", _pwd_cwd.path);
}
