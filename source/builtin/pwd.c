/*
 * pwd built-in
 *
 * Tracks the current working directory and provides
 * helpers for cd to build paths incrementally.
 */

#include "pwd.h"

#include <stdio.h>

void builtin_pwd_cmd_run (const struct ParserTreeCmd *treeCmd)
{
	(void) treeCmd;
	printf("pwd invoked\n");
}
