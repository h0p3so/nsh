#include "lex.h"
#include "post.h"

#include <stdio.h>
#include <unistd.h>

#define NSH_MAIN_CMDLINE_MAX_LENGTH 4096

static void _setup (void)
{
	setbuf(stdout, NULL);
}

static void _repl ()
{
	char cmdline[NSH_MAIN_CMDLINE_MAX_LENGTH] = {0};
	while (true)
	{
		printf("$ ");
		const size_t cmdlineLength = read(STDIN_FILENO, cmdline, NSH_MAIN_CMDLINE_MAX_LENGTH);
		cmdline[cmdlineLength - 1] = '\0';

		struct LexToken *stream = lex_gen_stream(cmdline, cmdlineLength);
		if (stream == NULL)
		{ continue; }

		const bool isbuiltin = post_is_builtin(stream);
		if (isbuiltin)
		{ continue; }

		lex_free_stream(stream);
	}
}

int main (void)
{
	_setup();
	_repl();
	return 0;
}
