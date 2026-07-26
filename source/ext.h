/*
 * external commands
 *
 * Searches the PATH for executables, verifies them
 * with stat, and runs them via fork and execve.
 */

#ifndef NSH_EXT_H
#define NSH_EXT_H

#include "shared/parsertok.h"
#include "shared/pathinfo.h"

typedef char ext_path_t[NSH_SHARED_PATHINFO_PATH_MAX + NSH_SHARED_PATHINFO_NAME_MAX];

bool ext_is_command_external (const char*, ext_path_t*);
void ext_run_external (const ext_path_t, const struct ParserTreeCmd*);

#endif
