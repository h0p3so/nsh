#ifndef NSH_LEX_H
#define NSH_LEX_H

#include "common/lextypes.h"

struct LexToken *lex_gen_stream (const char*, const size_t);
void lex_free_stream (const struct LexToken*);

#endif
