#include "echo.h"

#include <stdio.h>

void echo_builtin_run (const struct LexToken *head, const struct LexToken *body)
{
	printf("%s\n", head->source + head->length);
}
