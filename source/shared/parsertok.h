/*
 * parser tree types
 *
 * Defines the command tree node structure used by
 * the parser to represent parsed commands and their
 * arguments.
 */

#ifndef NSH_SHARED_PARSERTOK_H
#define NSH_SHARED_PARSERTOK_H

#include "comm.h"

enum ParserTreeCmdType
{
	PARSER_TREE_CMD_TYPE_COMMAND,
};

struct ParserTreeCmd;
struct ParserTreeCmd
{
	/* a command looks like this:
	 * command [arguments ...]
	 * 
	 * for example
	 *
	 * ls -lA --color --author
	 *
	 * ls:                       head
	 * [-lA, --color, --author]: argv (uses stdv)
	 */
	struct
	{
		/* head field points to the first element within argv, therfore
		 * it shall not be freeded
		 */
		char *head;
		char **argv;
	} commandRelated;

	struct ParserTreeCmd *lhs;
	struct ParserTreeCmd *rhs;
	enum ParserTreeCmdType type;
};

#endif
