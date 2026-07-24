#include "type.h"
#include "../builtin.h"
#include "libs/stdv.h"

#include <stdio.h>
#include <string.h>

#include <sys/stat.h>

#ifndef PATH_MAX
	#define PATH_MAX 4096
#endif

#ifndef NAME_MAX
	#define NAME_MAX 256
#endif

#define _BUILTIN_TYPE_MAX_PATHS 32
#define _BUILTIN_TYPE_ENVPATH_DELIMITERS ":;"

struct Path
{
	char path[PATH_MAX];
	size_t length;
};

struct TotalPaths
{
	struct Path paths[_BUILTIN_TYPE_MAX_PATHS];
	size_t total;
};

enum StatOver
{
	STAT_OVER_IS_DIR,
	STAT_OVER_IS_EXE,
};

static const struct TotalPaths *_builtin_type_load_paths (const bool);
static bool _builtin_type_stat_over (const char*, const enum StatOver);

static bool _builtin_is_external (const char*, char (*)[PATH_MAX + NAME_MAX]);

void builtin_type_cmd_run (const struct ParserTreeCmd *treeCmd)
{
	if (stdv_size(treeCmd->commandRelated.argv) == 0)
	{ return; }

	const char *cmdname = stdv_get(treeCmd->commandRelated.argv, 0);
	const struct BuiltInCmd *isbuiltin = builtin_get(cmdname);

	if (isbuiltin)
	{ printf("%s is a shell builtin\n", cmdname); return; }


	/* In order not to allocate space on the heap, we define a large
	 * buffer from the caller function in order to it to be overwritten
	 * by _builtin_is_external in case the command is indeed external
	 */
	char placeholder[PATH_MAX + NAME_MAX] = {0};
	const bool isexternal = _builtin_is_external(cmdname, &placeholder);

	if (isexternal)
	{ printf("%s is %s\n", cmdname, placeholder); return; }

	printf("%s: not found\n", cmdname);
}

static const struct TotalPaths *_builtin_type_load_paths (const bool force)
{
	static struct TotalPaths tpaths = {0};
	static bool performed = false;

	const char *envPaths = getenv("PATH");
	const size_t lim = strlen(envPaths);

	if (performed && force == false)
	{ return &tpaths; }

	for (size_t i = 0; i < lim && tpaths.total < _BUILTIN_TYPE_MAX_PATHS; i++)
	{
		const size_t pathlen = strcspn(envPaths + i, _BUILTIN_TYPE_ENVPATH_DELIMITERS);
		if (pathlen > PATH_MAX)
		{ continue; }

		struct Path path = { .length = pathlen };
		strncpy(path.path, envPaths + i, path.length);

		i += pathlen;
		if (_builtin_type_stat_over(path.path, STAT_OVER_IS_DIR) == false)
		{ continue; }

		memcpy(&tpaths.paths[tpaths.total++], &path, sizeof(path));
	}

	performed = true;
	return &tpaths;
}

static bool _builtin_type_stat_over (const char *path, const enum StatOver op)
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

static bool _builtin_is_external (const char *cmdname, char (*placeholder)[PATH_MAX + NAME_MAX])
{
	const struct TotalPaths *tpaths = _builtin_type_load_paths(false);

	static const uint32_t plusSlash = 1;
	const size_t cmdnamelen = strlen(cmdname);

	for (size_t i = 0; i < tpaths->total; i++)
	{
		const struct Path path = tpaths->paths[i];
		const size_t fullpathlen = path.length + cmdnamelen + plusSlash;

		if (fullpathlen >= PATH_MAX + NAME_MAX)
		{ continue; }

		snprintf(*placeholder, fullpathlen + 1, "%s/%s", path.path, cmdname);

		if (_builtin_type_stat_over(*placeholder, STAT_OVER_IS_EXE))
		{ return true; }
	}

	return false;
}

