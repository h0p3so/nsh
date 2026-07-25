/*
 * built-in commands registry
 *
 * Stores all built-in commands in a sorted array
 * and looks them up by name with bsearch.
 */

#ifndef NSH_BUILTIN_H
#define NSH_BUILTIN_H

#include "shared/builtintypes.h"

const struct BuiltInCmd *builtin_get (const char*);

#endif
