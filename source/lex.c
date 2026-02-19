#include "lex.h"

#include <string.h>

struct LexToken lex_get_header (const char *prompt, const size_t promptLength)
{
	struct LexToken token = {
		.source = prompt,
		.length = strcspn(prompt, " \t\n"),
		.type   = LEX_TOK_TYPE_HEAD
	};
	return token;
}
