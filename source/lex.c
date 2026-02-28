#include "lex.h"
#include "libs/stdv.h"

#include <ctype.h>
#include <stdio.h>

static struct LexToken _get_word (const char *cmdline, size_t *pos)
{
	struct LexToken token = {
		.type = LEX_TOK_TYPE_WORD,
		.source = cmdline + *pos,
		.length = 0
	};

	while (isalpha(cmdline[*pos]))
	{ *pos = *pos + 1; token.length++; }
	return token;
}

struct LexToken *lex_gen_stream (const char *cmdline, const size_t cmdlineLength)
{
	struct LexToken *stream = stdv_create(sizeof(struct LexToken), STDV_STD_INIT_CAP);

	for (size_t i = 0; i < cmdlineLength; i++)
	{
		const char a = cmdline[i];
		if (isspace(a)) continue;
		if (isalpha(a))
		{
			struct LexToken word = _get_word(cmdline, &i);
			stdv_put(stream, word);
			continue;
		}
	}

	return (stdv_size(stream)) ? stream : NULL;
}

void lex_free_stream (const struct LexToken *stream)
{
	stdv_free(stream);
}
