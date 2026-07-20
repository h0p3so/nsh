#ifndef NSH_CMD_H
#define NSH_CMD_H

#include "common/common.h"
#include <stdio.h>

#define NSH_CMD_NUM_BUILT_IN_CMDS 2

const void* cmd_init_or_get_builtin_cmds (void);

bool cmd_search_builtin (const char*, const size_t);

#endif
