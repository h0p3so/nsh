/*
 * parser
 *
 * Converts a token stream into a command tree.
 * Each node represents a command with its name
 * and argument list.
 */

#ifndef NSH_PARSER_H
#define NSH_PARSER_H

#include "shared/lextok.h"
#include "shared/parsertok.h"

const struct ParserTreeCmd *parse_produce_tree (const struct LexTok*);
void parse_free_tree (const struct ParserTreeCmd*);

#endif
