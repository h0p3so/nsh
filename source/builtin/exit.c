#include "builtin.h"

#include <stdio.h>
#include <stdlib.h>

void builtin_exit_cmd_run (const struct ParserTreeCmd*)
{
	printf("nsh says goodbye...\n");
	exit(0);
}
