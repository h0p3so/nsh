/*
 * pwd built-in
 *
 * Tracks the current working directory and provides
 * helpers for cd to build paths incrementally.
 */

#include "pwd.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>

static struct PathPath _builtin_pwd_cwd;

const struct PathPath *builtin_pwd_get_cwd (void)
{
	static bool firstcall = true;

	if (firstcall)
	{
		getcwd(_builtin_pwd_cwd.path, NSH_SHARED_PATHINFO_PATH_MAX); // TODO handle
		_builtin_pwd_cwd.length = strlen(_builtin_pwd_cwd.path);
		firstcall = false;
	}

	return &_builtin_pwd_cwd;
}

void builtin_pwd_update (const struct PathPath *resolved)
{
	memcpy(_builtin_pwd_cwd.path, resolved->path, resolved->length);
	_builtin_pwd_cwd.path[resolved->length] = '\0';
	_builtin_pwd_cwd.length = resolved->length;
}

void builtin_pwd_cmd_run (const struct ParserTreeCmd *treeCmd)
{
	(void) treeCmd;
	printf("%s\n", builtin_pwd_get_cwd()->path);
}
