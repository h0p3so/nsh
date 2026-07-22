/*
 * AndOr (&&)
 * ├── lhs: Pipeline
 * │   ├── Command
 * │   │   ├── head: "grep"
 * │   │   ├── argv: ["grep", "-i", "error"]
 * │   │   └── redirections: [ stdin <- "log.txt" ]
 * │   │
 * │   ├── Command
 * │   │   ├── head: "sort"
 * │   │   ├── argv: ["sort"]
 * │   │   └── redirections: none
 * │   │
 * │   └── Command
 * │       ├── head: "uniq"
 * │       ├── argv: ["uniq", "-c"]
 * │       └── redirections: [ stdout -> "report.txt" ]
 * │
 * └── rhs: Command
 *     ├── head: "echo"
 *     ├── argv: ["echo", "done"]
 *     └── redirections: none
 * 
 * 
 * Command
 * ├── argv: ["echo", "hola", "como", "has", "estado"]
 * └── redirections: none
 */

#include "req.h"
#include "builtin.h"

static bool _req_is_builtin (const struct ParserTreeCmd*);

bool req_process (const struct ParserTreeCmd *treeCmd)
{
	if (treeCmd->type == PARSER_TREE_CMD_TYPE_COMMAND)
	{
		return _req_is_builtin(treeCmd);
	}
	return false;
}


static bool _req_is_builtin (const struct ParserTreeCmd *treeCmd)
{
	const char *cmdName = treeCmd->commandRelated.head;
	const struct BuiltInCmd *builtin = builtin_get(cmdName);

	if (builtin == NULL)
	{ return false; }

	builtin->run(treeCmd);
	return true;
}
