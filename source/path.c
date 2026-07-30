#include "path.h"

#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <stdlib.h>

#define _PATH_REL_START  '.'
#define _PATH_ABS_START  '/'
#define _PATH_HOME_START '~'

static struct Path _path_resolve (const char*);

struct Path path_get_cwd (void)
{
	const char *cw = getcwd(NULL, 0);

	struct Path p = { .length = strlen(cw), .isInvalid = false };
	strncpy(p.path, cw, p.length);

	return p;
}

struct Path path_get_home (void)
{
	const char *home = getenv("HOME");

	struct Path p = { .length = strlen(home), .isInvalid = false };
	strncpy(p.path, home, p.length);

	return p;
}

struct Path path_resolve (const char *raw)
{
	char midterm[NSH_SHARED_PATHINFO_PATH_MAX] = {0};
	const size_t rawlen = strlen(raw);

	// TODO: handle base cases such as ~ . or /

	if (*raw == _PATH_REL_START && rawlen == 1)
	{
		const struct Path curdir = path_get_cwd();
		strncpy(midterm, curdir.path, NSH_SHARED_PATHINFO_PATH_MAX);
		printf("using rel: %s\n", midterm);
	}
	else if (*raw == _PATH_ABS_START)
	{
		strncpy(midterm, raw, NSH_SHARED_PATHINFO_PATH_MAX);
		printf("using abs: %s\n", midterm);
	}
	else if (*raw == _PATH_HOME_START)
	{
		const struct Path home = path_get_home();
		const size_t rawlenwithnotilde = rawlen - 1;

		if (rawlenwithnotilde + home.length >= NSH_SHARED_PATHINFO_PATH_MAX)
		{ /* TODO */ }

		/* no slash is included in the format since it is given as a matter of fact
		 * what an slash should go right after ~. If it does not, it will provoke an
		 * error soon jeje
		 */
		snprintf(midterm, rawlenwithnotilde + home.length + 1, "%s%s", home.path, raw + 1);
		printf("using home: %s\n", midterm);
	}
	else
	{
		size_t skip = 0;
		if (*raw == '.' && rawlen > 1 && raw[1] == '/')
		{ skip = 2; }

		const struct Path curdir = path_get_cwd();

		if (((rawlen - skip) + curdir.length) >= NSH_SHARED_PATHINFO_PATH_MAX)
		{ /* TODO */ }

		snprintf(midterm, curdir.length + (rawlen - skip) + 2, "%s/%s", curdir.path, raw + skip);
		printf("using curdir: %s\n", midterm);
	}


	return _path_resolve(midterm);
}

static struct Path _path_resolve (const char *midterm)
{
	struct Path path = {0};
	const size_t lim = strlen(midterm);

	path.path[path.length++] = '/';

	for (size_t i = 0; i < lim && !path.isInvalid && path.length < NSH_SHARED_PATHINFO_PATH_MAX; i++)
	{
		const bool theresroom = ((i + 1) < lim);

		if (midterm[i] == '.' && theresroom && midterm[i + 1] == '/')
		{ /* TODO */ }
		if (midterm[i] == _PATH_HOME_START)
		{ /* TODO */ }

		const size_t start = i;
		while (midterm[i] != '/' && i < lim) i++;

		const size_t dirnamelen = i - start;
		const size_t dirnamelenWithSlash = dirnamelen + 1;

		if (dirnamelen == 0)
		{ continue; }

		const char *dirname = midterm + start;
		if (dirnamelen == 2 && dirname[0] == '.' && dirname[1] == '.' && path.length >= 2)
		{
			/* skips the null byte terminator and the last slash added */
			path.length -= 2;

			while (path.length > 0 && path.path[path.length--] != '/')
				;;

			path.path[++path.length] = '/';
			path.path[++path.length] = '\0';

			continue;
		}

		path.length += snprintf(
			path.path + path.length,
			dirnamelenWithSlash + 1,
			"%.*s",
			(uint32_t) dirnamelenWithSlash,
			dirname
		);
	}

	if (path.path[path.length - 1] == '/')
	{ path.path[--path.length] = '\0'; }

	printf("final: %s <%d> (%ld)\n", path.path, path.path[path.length], path.length);
	puts("-*-*-");
	return path;
}

//home/exupery/Documents/programming/lowlevel/nsh/source/..
