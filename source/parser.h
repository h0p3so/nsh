#ifndef NSH_PARSER_H
#define NSH_PARSER_H

#include "shared/lextok.h"
#include "shared/parsertok.h"

const struct ParserTreeCmd *parse_produce_tree (const struct LexTok*);
void parse_free_tree (const struct ParserTreeCmd*);

#endif
