#ifndef NSH_COMMON_LEXTYPES_H
#define NSH_COMMON_LEXTYPES_H

#include "common.h"

enum LexTokenType
{
	LEX_TOK_TYPE_HEAD,
};

struct LexToken
{
	const char *source;
	const size_t length;
	const enum LexTokenType type;
};

#endif
