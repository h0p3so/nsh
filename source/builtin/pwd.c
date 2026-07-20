#include "pwd.h"
#include "../err.h"
#include "../shared/pathmax.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <pwd.h>

#define _BUILTIN_PWD_STAGE_NAME "builtin-pwd"

struct IntCwd
{
	char path[NSH_SHARED_PATHMAX_PATH_MAX];
	size_t length;
};

/* this IntCwd contains the full path of the current working directory, in other
 * words it is $PWD
 */
static struct IntCwd _builtin_pwd_cwd = {0};

/* this IntCwd acts as a relative path builder which is used when the `cd` command
 * is parsing a new path
 */
static struct IntCwd _builtin_pwd_aux_cwd = {0};

void builtin_pwd_set_origin (void)
{
	static bool set = false;
	if (set)
	{ return; }

	memset(_builtin_pwd_cwd.path, 0, NSH_SHARED_PATHMAX_PATH_MAX);
	_builtin_pwd_cwd.length = 0;

	memset(_builtin_pwd_aux_cwd.path, 0, NSH_SHARED_PATHMAX_PATH_MAX);
	_builtin_pwd_aux_cwd.length = 0;

	const char *envv = getenv("PWD");
	if (envv)
	{
		strncpy(_builtin_pwd_cwd.path, envv, NSH_SHARED_PATHMAX_PATH_MAX);
		set = true;
		return;
	}

	const char *ret = getcwd(_builtin_pwd_cwd.path, NSH_SHARED_PATHMAX_PATH_MAX);
	if (ret == NULL)
	{ err_fatal(_BUILTIN_PWD_STAGE_NAME, "trying to get the current working directory"); }

	set = true;
}

const char *builtin_pwd_get_home (void)
{
	return  getenv("HOME");

	static char home[NSH_SHARED_PATHMAX_PATH_MAX] = {0};
	static bool set = false;

	if (set)
	{ return home; }

	struct passwd *pw = getpwuid(getuid());
	if (pw == NULL)
	{ err_fatal(_BUILTIN_PWD_STAGE_NAME, "trying to access user's information"); }

	strncpy(home, pw->pw_dir, NSH_SHARED_PATHMAX_PATH_MAX);
	set = true;
	return home;
}

void builtin_pwd_aux_add (const char *portion, const size_t length)
{
	if (_builtin_pwd_aux_cwd.length + length >= NSH_SHARED_PATHMAX_PATH_MAX)
	{ /* TODO */ }

	snprintf(
		_builtin_pwd_aux_cwd.path + _builtin_pwd_aux_cwd.length,
		1 + length,
		"%s",
		portion
	);
	_builtin_pwd_aux_cwd.length += length;
}

void builtin_pwd_aux_complete (void)
{
	strncpy(
		_builtin_pwd_cwd.path,
		_builtin_pwd_aux_cwd.path,
		NSH_SHARED_PATHMAX_PATH_MAX
	);

	memset(_builtin_pwd_aux_cwd.path, 0, _builtin_pwd_aux_cwd.length);
	_builtin_pwd_aux_cwd.length = 0;
}

const char *builtin_pwd_get_cwd (void)
{
	return _builtin_pwd_cwd.path;
}

void builtin_pwd_cmd_run (const struct ParserTreeCmd *treeCmd)
{
	(void) treeCmd;
	printf("%s\n", getcwd(NULL, 0));
}

