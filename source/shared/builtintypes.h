/*
 * built-in command types
 *
 * Defines the struct and function pointer type used
 * to register and call built-in commands.
 */

#ifndef NSH_SHARED_BUILTIN_TYPES_H
#define NSH_SHARED_BUILTIN_TYPES_H

#include "comm.h"
#include "parsertok.h"

typedef void (*builtin_run_t) (const struct ParserTreeCmd*);

struct BuiltInCmd
{
	const char *name;
	const char *help;
	const builtin_run_t run;
};

#endif
