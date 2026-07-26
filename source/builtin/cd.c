/*
 * cd built-in
 *
 * Changes the current directory. Supports ~ as an
 * alias for the user's home directory.
 */

#include "cd.h"
#include "../path.h" // XXX

#include <stdio.h>

#include <stdlib.h>

void builtin_cd_cmd_run (const struct ParserTreeCmd *treeCmd)
{
	(void) treeCmd;

	path_resolve(".");
	path_resolve("/abc");
	path_resolve("~/abc");
	path_resolve("abc");

	puts("===");
	path_resolve("../..");

	puts("===");
	path_resolve("~/Documents/../../../../../../");

	puts("===");
	path_resolve("~/Documents/../../..............");
	exit(0);
}
