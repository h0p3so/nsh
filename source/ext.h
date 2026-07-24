#ifndef NSH_EXT_H
#define NSH_EXT_H

#include "shared/comm.h"

#define NSH_EXT_PATH_MAX 4096
#define NSH_EXT_NAME_MAX  256

typedef char ext_path_t[NSH_EXT_PATH_MAX + NSH_EXT_NAME_MAX];

bool ext_is_command_external (const char*, ext_path_t*);

#endif
