/*
 * external commands
 *
 * Searches the PATH for executables, verifies them
 * with stat, and runs them via fork and execve.
 */

#include "ext.h"
#include "err.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define _EXT_MAX_PATHS 32
#define _EXT_ENVPATH_DELIMITERS ":;"

#define _EXT_STAGE_NAME "external"

struct Path
{
	char path[NSH_SHARED_PATHINFO_PATH_MAX];
	size_t length;
};

struct TotalPaths
{
	struct Path paths[_EXT_MAX_PATHS];
	size_t total;
};

enum StatOver
{
	STAT_OVER_IS_DIR,
	STAT_OVER_IS_EXE,
};

static const struct TotalPaths *_ext_load_paths (const bool);
static bool _ext_stat_over (const char*, const enum StatOver);

bool ext_is_command_external (const char *cmdname, ext_path_t *dest)
{
	const struct TotalPaths *tpaths = _ext_load_paths(false);

	static const uint32_t plusSlash = 1;
	const size_t cmdnamelen = strlen(cmdname);

	for (size_t i = 0; i < tpaths->total; i++)
	{
		const struct Path path = tpaths->paths[i];
		const size_t fullpathlen = path.length + cmdnamelen + plusSlash;

		if (fullpathlen >= NSH_SHARED_PATHINFO_PATH_MAX + NSH_SHARED_PATHINFO_NAME_MAX)
		{ continue; }

		snprintf(*dest, fullpathlen + 1, "%s/%s", path.path, cmdname);

		if (_ext_stat_over(*dest, STAT_OVER_IS_EXE))
		{ return true; }
	}

	return false;
}

static const struct TotalPaths *_ext_load_paths (const bool force)
{
	static struct TotalPaths tpaths = {0};
	static bool performed = false;

	const char *envPaths = getenv("PATH");
	const size_t lim = strlen(envPaths);

	if (performed && force == false)
	{ return &tpaths; }

	for (size_t i = 0; i < lim && tpaths.total < _EXT_MAX_PATHS; i++)
	{
		const size_t pathlen = strcspn(envPaths + i, _EXT_ENVPATH_DELIMITERS);
		if (pathlen > NSH_SHARED_PATHINFO_PATH_MAX)
		{ continue; }

		struct Path path = { .length = pathlen };
		strncpy(path.path, envPaths + i, path.length);

		i += pathlen;
		if (_ext_stat_over(path.path, STAT_OVER_IS_DIR) == false)
		{ continue; }

		memcpy(&tpaths.paths[tpaths.total++], &path, sizeof(path));
	}

	performed = true;
	return &tpaths;
}

static bool _ext_stat_over (const char *path, const enum StatOver op)
{
	struct stat s;
	if (stat(path, &s) != 0)
	{ return false; }

	switch (op)
	{
		case STAT_OVER_IS_DIR: return S_ISDIR(s.st_mode);
		case STAT_OVER_IS_EXE: return S_ISREG(s.st_mode) && (s.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH));
	}
	return false;
}

void ext_run_external (const ext_path_t path, const struct ParserTreeCmd *treeCmd)
{
	pid_t childpid = fork();

	if (childpid == -1)
	{ err_fatal(_EXT_STAGE_NAME, "trying to fork current process"); }

	if (childpid == 0)
	{ execve(path, treeCmd->commandRelated.argv, NULL); }
	else
	{
		static const int32_t anychild = -1;
		int32_t wstatus;

		do { (void) waitpid(anychild, &wstatus, WUNTRACED); }
		while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
	}
}

