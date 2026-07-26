#ifndef NSH_PATH_H
#define NSH_PATH_H

#include "shared/comm.h"
#include "shared/pathinfo.h"

struct Path
{
	char path[NSH_SHARED_PATHINFO_PATH_MAX];
	size_t length;
	bool isInvalid;
};

struct Path path_get_cwd (void);
struct Path path_get_home (void);

struct Path path_resolve (const char*);

#endif
