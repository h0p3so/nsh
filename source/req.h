/*
 * request dispatcher
 *
 * Routes a parsed command to either a built-in
 * handler or an external executable. Returns true
 * if the command was found and executed.
 */

#ifndef NSH_REQ_H
#define NSH_REQ_H

#include "shared/parsertok.h"

bool req_process (const struct ParserTreeCmd*);

#endif
