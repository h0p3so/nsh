/*
 * pwd built-in
 *
 * Tracks the current working directory and provides
 * helpers for cd to build paths incrementally.
 */

#include "pwd.h"
#include "../err.h"
#include "../shared/pathmax.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <pwd.h>

#define _BUILTIN_PWD_STAGE_NAME "builtin-pwd"

#define _BUILTIN_PWD_ABS_PATH_SPECIFIER '/'
#define _BUILTIN_PWD_REL_PATH_SPECIFIER '.'

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

static void _builtin_pwd_suregy (void);

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

// TODO try to get it via $HOME
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
	{
		errno = ENAMETOOLONG;
		err_fatal(_BUILTIN_PWD_STAGE_NAME, "accessing an indicated path");
	}

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
	_builtin_pwd_suregy();
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

static void _builtin_pwd_suregy (void)
{
	struct IntCwd final = {0};

	if (_builtin_pwd_aux_cwd.path[0] == '/')
	{
		final.path[0] = '/';
		final.length++;
	}

	const size_t lim = _builtin_pwd_aux_cwd.length;
	/* when the command gets to this function, the whole _builtin_pwd_aux_cwd.path
	 * will be made of valid characters accepted by the lexer, no variables no aliases
	 * only real paths
	 */
	for (size_t i = 0; i < lim; i++)
	{
		const bool theresroom = ((i + 1) < lim);

		if (_builtin_pwd_aux_cwd.path[i] == '.' && theresroom && _builtin_pwd_aux_cwd.path[i + 1] == '/')
		{ i++; continue; }

		const size_t starting = i;
		while (_builtin_pwd_aux_cwd.path[i] != '/' && i < lim) i++;

		const size_t dirnamelen = i - starting;
		const size_t dirnamelenWithSlash = dirnamelen + 1;

		if (dirnamelen == 0)
		{ continue; }

		const char *dirname = _builtin_pwd_aux_cwd.path + starting;
		if (dirnamelen == 2 && dirname[0] == '.' && dirname[1] == '.' && final.length >= 2)
		{
			/* skips the null byte terminator and the last slash added */
			final.length -= 2;

			while (final.length > 0 && final.path[final.length--] != '/')
				;;

			final.path[++final.length] = '/';
			final.path[++final.length] = '\0';

			continue;
		}

		strncpy(
			final.path + final.length,
			dirname,
			dirnamelenWithSlash
		);
		final.length += dirnamelenWithSlash;
	}

	if (final.path[final.length - 1] == '/')
	{ final.path[--final.length] = '\0'; }

	printf("final path: %s\n", final.path);

	strncpy(
		_builtin_pwd_cwd.path,
		final.path,
		NSH_SHARED_PATHMAX_PATH_MAX
	);
	_builtin_pwd_cwd.length = final.length;
}
