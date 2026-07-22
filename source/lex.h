#ifndef NSH_LEX_H
#define NSH_LEX_H

#include "shared/comm.h"

enum LexTokType
{
	LEX_TOK_TYPE_EOL,
	LEX_TOK_TYPE_WORD,
	LEX_TOK_TYPE_PIPE,
};

struct LexTok
{
	char *source;
	size_t length;
	enum LexTokType type;
};

const struct LexTok* lex_produce_stream (const char*, const size_t);

#endif
