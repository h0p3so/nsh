#include "lex.h"
#include "post.h"

#include <stdio.h>
#include <unistd.h>

#define NSH_MAIN_PROMPT_MAX_LENGTH 4096

static void _setup (void)
{
	setbuf(stdout, NULL);
}

static void _repl ()
{
	char prompt[NSH_MAIN_PROMPT_MAX_LENGTH] = {0};
	while (true)
	{
		printf("$ ");
		const size_t promptLength = read(STDIN_FILENO, prompt, NSH_MAIN_PROMPT_MAX_LENGTH);
		prompt[promptLength - 1] = '\0'; // XXX: temp solution

		const struct LexToken head = lex_get_header(prompt, promptLength);

		if (post_is_builtin(&head))
		{ continue; }

		printf("%.*s: command not found\n", (uint32_t) head.length, head.source);
	}
}

int main (void)
{
	_setup();
	_repl();
	return 0;
}
