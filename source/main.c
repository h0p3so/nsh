#include "cmd.h"

#include <stdbool.h>
#include <unistd.h>

static void setup (void)
{
	/* prevents buffering */
	setbuf(stdout, NULL);

	(void) cmd_init_or_get_builtin_cmds();
}

static void repl (void)
{
	char buffer[NSH_COMM_BUFFER_SIZE] = {0};
	while (true)
	{
		printf("$ ");
		const size_t bytes = read(STDIN_FILENO, buffer, NSH_COMM_BUFFER_SIZE);

		buffer[bytes - 1] = '\0';

		const bool itsBuiltin = cmd_search_builtin(buffer, bytes);
		if (itsBuiltin)
		{ continue; }

		printf("%s: command not found\n", buffer);
	}
}

int main (int argc, char **argv)
{
	setup();
	repl();
	return 0;
}
