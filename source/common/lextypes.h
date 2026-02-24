#ifndef NSH_COMMON_LEXTYPES_H
#define NSH_COMMON_LEXTYPES_H

#include "common.h"

enum LexTokenType
{
	LEX_TOK_TYPE_WORD,
};

struct LexToken
{
	char *source;
	size_t length;
	enum LexTokenType type;
};

#endif
