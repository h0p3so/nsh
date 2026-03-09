#include "shared/comm.h"
#include "parser.h"
#include "lex.h"

#include <stdio.h>
#include <unistd.h>

#define _MAIN_CMDLINE_MAX_LENGTH 1024

static void _main_setup (void)
{
	setbuf(stdout, NULL);
}

static void _main_repl (void)
{
	char cmdline[_MAIN_CMDLINE_MAX_LENGTH] = {0};
	while (true)
	{
		printf("$ ");

		const size_t cmdlinelen = read(STDIN_FILENO, cmdline, _MAIN_CMDLINE_MAX_LENGTH);
		if (cmdlinelen == 1)
		{ continue; }

		const struct LexTok *stream = lex_produce_stream(cmdline, cmdlinelen);
		const struct ParserTreeCmd *treeCmd = parse_produce_tree(stream);

		parse_free_tree(treeCmd);
		lex_free_stream(stream);
	}
}

int main (void)
{
	_main_setup();
	_main_repl();
	return 0;
}


