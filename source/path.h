#ifndef NSH_PATH_H
#define NSH_PATH_H

#include "shared/comm.h"
#include "shared/pathinfo.h"

struct PathPath path_get_cwd (void);
struct PathPath path_resolve (const char*);

#endif
