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

static char* _builtin_pwd_cwd;

static const char *_builtin_pwd_get_home (void);

void builtin_pwd_set_origin (void)
{
	static bool set = false;
	if (set)
	{ return; }

	_builtin_pwd_cwd = calloc(NSH_SHARED_PATHMAX_PATH_MAX, sizeof(char));
	NSH_ERR_CHECKPTR(_builtin_pwd_cwd, _BUILTIN_PWD_STAGE_NAME, "allocating space for PWD var");

}

void builtin_pwd_cmd_run (const struct ParserTreeCmd *treeCmd)
{
	(void) treeCmd;
	printf("%s\n", _builtin_pwd_cwd);
}

void builtin_pwd_go_home (void)
{
	const char *homepath = _builtin_pwd_get_home();
	chdir(homepath);
}

void builtin_pwd_clean (void)
{
	if (_builtin_pwd_cwd == NULL)
	{ return; }

	free(_builtin_pwd_cwd);
}

static const char *_builtin_pwd_get_home (void)
{
	char *home = getenv("HOME");

	if (home == NULL)
	{
		struct passwd *pw = getpwuid(getuid());
		if (pw == NULL)
		{ err_fatal(_BUILTIN_PWD_STAGE_NAME, "trying to access user's information"); }

		strncpy(_builtin_pwd_cwd, pw->pw_dir, NSH_SHARED_PATHMAX_PATH_MAX);
	}
	else
	{ strncpy(_builtin_pwd_cwd, home, NSH_SHARED_PATHMAX_PATH_MAX); }

	return home;
}
