#ifndef NSH_LEX_H
#define NSH_LEX_H

#include "common/lextypes.h"

struct LexToken *lex_gen_stream (const char*, const size_t);
void lex_gen_free_stream (struct LexToken*);

#endif
