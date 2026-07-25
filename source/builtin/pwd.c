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
	char *path; // XXX do not use heap
	size_t length;
};

static struct IntCwd _builtin_pwd_cwd = {0};
static struct IntCwd _builtin_pwd_aux_cwd = {0};

void builtin_pwd_set_origin (void)
{
	static bool set = false;
	if (set)
	{ return; }

	_builtin_pwd_cwd.path = calloc(NSH_SHARED_PATHMAX_PATH_MAX, sizeof(char));
	_builtin_pwd_cwd.length = 0;
	NSH_ERR_CHECKPTR(_builtin_pwd_cwd.path, _BUILTIN_PWD_STAGE_NAME, "allocating space for CWD var");

	_builtin_pwd_aux_cwd.path = calloc(NSH_SHARED_PATHMAX_PATH_MAX, sizeof(char));
	_builtin_pwd_aux_cwd.length = 0;
	NSH_ERR_CHECKPTR(_builtin_pwd_aux_cwd.path, _BUILTIN_PWD_STAGE_NAME, "allocating space for aux CWD var");

	const char *envv = getenv("PWD");
	if (envv)
	{ strncpy(_builtin_pwd_cwd.path, envv, NSH_SHARED_PATHMAX_PATH_MAX); return; }

	const char *ret = getcwd(_builtin_pwd_cwd.path, NSH_SHARED_PATHMAX_PATH_MAX);

	if (ret == NULL)
	{ err_fatal(_BUILTIN_PWD_STAGE_NAME, "trying to get the current working directory"); }
	set = true;
}

const char *builtin_pwd_get_home (void)
{
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

	printf("rn: %s\n", _builtin_pwd_aux_cwd.path);
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
	printf("%s\n", _builtin_pwd_cwd.path);
}

void builtin_pwd_clean (void) // XXX remove this
{
	if (_builtin_pwd_cwd.path)
	{ free(_builtin_pwd_cwd.path); }

	if (_builtin_pwd_aux_cwd.path)
	{ free(_builtin_pwd_aux_cwd.path); }
}

