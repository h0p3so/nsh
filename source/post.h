#ifndef NSH_POSH_H
#define NSH_POSH_H

#include "common/lextypes.h"

bool post_is_builtin (const struct LexToken*);
bool post_is_external (const struct LexToken*);

#endif
