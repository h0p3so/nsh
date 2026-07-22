#include "echo.h"
#include "libs/stdv.h"

#include <stdio.h>

void builtin_echo_cmd_run (const struct ParserTreeCmd *treeCmd)
{
	const size_t size = stdv_size(treeCmd->commandRelated.argv);

	for (size_t i = 0; i < size; i++)
	{
		const char *argv = stdv_get(treeCmd->commandRelated.argv, i);
		const char trailing = ((i + 1) == size) ? '\n' : ' ';
		printf("%s%c", argv, trailing);
	}
}
