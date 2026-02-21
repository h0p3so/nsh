#include "exit.h"
#include <stdlib.h>

void exit_builtin_run (const struct LexToken *head, const struct LexToken *body)
{
	exit(0);
}

