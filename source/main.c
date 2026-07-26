/*
 * nsh - naive shell
 *
 * Sets up the REPL, reads input from stdin and
 * drives the pipeline: lexing, parsing, execution.
 */

#include "builtin/pwd.h"
#include "shared/comm.h"
#include "parser.h"
#include "lex.h"
#include "req.h"

#include <stdio.h>
#include <unistd.h>

#define _MAIN_CMDLINE_MAX_LENGTH 1024

static void _main_setup (void);
static void _main_repl (void);

int main (void)
{
	_main_setup();
	_main_repl();
	return 0;
}

static void _main_setup (void)
{
	//builtin_pwd_set_origin();
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
		struct ParserTreeCmd *treeCmd = parse_produce_tree(stream);

		const bool ok = req_process(treeCmd);
		if (ok == false)
		{
			const struct LexTok head = *stream;
			printf("%.*s: command not found\n", (uint32_t) head.length, head.source);
		}

		lex_free_stream(stream);
		treeCmd = parse_free_tree(treeCmd);
	}
}
