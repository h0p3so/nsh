#ifndef NSH_SHARED_LEXTOK_H
#define NSH_SHARED_LEXTOK_H

#include "comm.h"

enum LexTokType
{
	LEX_TOK_TYPE_EOL,
	LEX_TOK_TYPE_WORD,
	LEX_TOK_TYPE_PIPE,
};

/* lexer produces tokens whose `source` field points to the buffer (cmdline)
 * from the caller function. The lexer does not allocate space in the heap
 * but rather it stores the position where the substring was seen in the buffer
 * and the length of the token
 */
struct LexTok
{
	const char *source;
	size_t length;
	enum LexTokType type;
};

#endif
