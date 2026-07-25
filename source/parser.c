/*
 * parser
 *
 * Converts a token stream into a command tree.
 * Each node represents a command with its name
 * and argument list.
 */

#include "parser.h"
#include "libs/stdv.h"
#include "shared/checkptr.h"

#include <stdlib.h>

#define _PARSER_STAGE_NAME "parsing"

static struct ParserTreeCmd* _parse_create_node (const enum ParserTreeCmdType);
static char* _parse_create_word (const char*, const size_t);

static struct ParserTreeCmd* _parse_parse_command (const struct LexTok*, const size_t);

const struct ParserTreeCmd *parse_produce_tree (const struct LexTok *stream)
{
	return _parse_parse_command(stream, 0);
}

void parse_free_tree (const struct ParserTreeCmd *treeCmd)
{
	// TODO
}

static struct ParserTreeCmd *_parse_create_node (const enum ParserTreeCmdType type)
{
	struct ParserTreeCmd *node = calloc(1, sizeof(struct ParserTreeCmd));
	NSH_SHARED_CHECKPTR(node, _PARSER_STAGE_NAME, "creating a new node");

	node->lhs  = NULL;
	node->rhs  = NULL;
	node->type = type;

	return node;
}

static char* _parse_create_word (const char *word, const size_t length)
{
	static const size_t plusNullByte = 1;

	char *mot = calloc(length + plusNullByte, sizeof(char));
	NSH_SHARED_CHECKPTR(mot, _PARSER_STAGE_NAME, "creating a new word");

	memcpy(mot, word, length);
	return mot;
}

static struct ParserTreeCmd* _parse_parse_command (const struct LexTok *stream, const size_t offset)
{
	struct ParserTreeCmd *node = _parse_create_node(PARSER_TREE_CMD_TYPE_COMMAND);
	const size_t lim = stdv_size(stream);

	/* creates the word at `offset` position within the `stream` stream
	 * as a PARSER_TREE_CMD_TYPE_COMMAND node
	 */
	node->commandRelated.head = _parse_create_word(
		stdv_get(stream, offset).source,
		stdv_get(stream, offset).length
	);

	node->commandRelated.argv = stdv_create(
		sizeof(*node->commandRelated.argv),
		STDV_STD_INIT_CAP
	);
	NSH_SHARED_CHECKPTR(node->commandRelated.argv, _PARSER_STAGE_NAME, "creating argv for current command");

	/* whatever comes next that is a word will be interpreted as an
	 * argv to the current command (node) including the `head`
	 */
	for (size_t i = offset; i < lim; i++)
	{
		const struct LexTok lextok = stdv_get(stream, i);
		if (lextok.type == LEX_TOK_TYPE_EOL)
		{ break; }

		if (lextok.type == LEX_TOK_TYPE_WORD)
		{
			stdv_put(
				node->commandRelated.argv,
				_parse_create_word(lextok.source, lextok.length)
			);
		}
	}
	return node;
}

