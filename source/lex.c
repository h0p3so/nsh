#include "lex.h"
#include "shared/checkptr.h"
#include "libs/stdv.h"

#include <ctype.h>

#define _LEX_STAGE_NAME "lexing"

static struct LexTok _lex_get_word (const char*, size_t*);

const struct LexTok* lex_produce_stream (const char *cmdline, const size_t cmdlinelen)
{
	static const struct LexTok newlinetok = {
		.source = NULL,
		.length = 0,
		.type   = LEX_TOK_TYPE_EOL
	};

	struct LexTok *stream = stdv_create(sizeof(struct LexTok), STDV_STD_INIT_CAP);
	NSH_SHARED_CHECKPTR(stream, _LEX_STAGE_NAME, "allocating space for token stream");

	bool EOLset = false;
	for (size_t i = 0; i < cmdlinelen; i++)
	{
		const char a = cmdline[i];
		if (a == '\n')
		{ EOLset = true; stdv_put(stream, newlinetok); break; }

		if (isspace(a))
		{ continue; }

		if (isalnum(a))
		{ stdv_put(stream, _lex_get_word(cmdline, &i)); }
	}

	if (EOLset == false)
	{ stdv_put(stream, newlinetok); }

	return stream;
}

void lex_free_stream (const struct LexTok *stream)
{
	stdv_free(stream);
}

static struct LexTok _lex_get_word (const char *cmdline, size_t *offset)
{
	struct LexTok tok = {
		.source = cmdline + *offset,
		.type   = LEX_TOK_TYPE_WORD,
		.length = 0
	};

	char a = tok.source[tok.length];
	while (isalnum(a) || a == '_' || a == '-')
	{
		tok.length++;
		*offset += 1;
		a = tok.source[tok.length];
	}

	*offset -= 1;
	return tok;
}
