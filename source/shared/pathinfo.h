/*
 * path length constants
 *
 * Maximum path and filename length limits used
 * throughout the shell.
 */

#ifndef NSH_SHARED_PATHINFO_H
#define NSH_SHARED_PATHINFO_H

#define NSH_SHARED_PATHINFO_PATH_MAX 4096
#define NSH_SHARED_PATHINFO_NAME_MAX  256

struct PathPath
{
	char path[NSH_SHARED_PATHINFO_PATH_MAX];
	size_t length;
};

#endif
