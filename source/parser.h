#ifndef NSH_PARSER_H
#define NSH_PARSER_H

#define NSH_PARSER_MAX_WORD_CAP 256

#include "shared/lextok.h"

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
		char *head;
		char **argv;
	} commandRelated;

	struct ParserTreeCmd *lhs;
	struct ParserTreeCmd *rhs;
	enum ParserTreeCmdType type;
};

const struct ParserTreeCmd *parse_produce_tree (const struct LexTok*);
void parse_free_tree (const struct ParserTreeCmd*);

#endif
