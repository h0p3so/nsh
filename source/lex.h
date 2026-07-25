/*
 * lexer
 *
 * Tokenizes a raw command-line string into a stream of
 * tokens: words, pipes, end-of-line markers etc. Tokens
 * do not own their data - they point into the caller's
 * buffer.
 */

#ifndef NSH_LEX_H
#define NSH_LEX_H

#include "shared/lextok.h"

const struct LexTok* lex_produce_stream (const char*, const size_t);
void lex_free_stream (const struct LexTok*);

#endif
