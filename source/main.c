#include "shared/comm.h"
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

		struct LexTok *stream = lex_produce_stream(cmdline, cmdlinelen);
	}
}

int main (void)
{
	_main_setup();
	_main_repl();
	return 0;
}


