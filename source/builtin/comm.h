#ifndef NSH_BUILTIN_COMM_H
#define NSH_BUILTIN_COMM_H

/* When `ParserTreeCmd.commandRelated.argv` parses
 * something like
 *
 * grep pattern file
 *
 * the argv vector will look like this:
 * [grep, pattern, file]
 *    ` includes the name of the executable in case it is an
 *      external command
 *
 * but for builtin commands that first string is unnecessary
 * so builtin commands need to skip it
 */
#define NSH_BUILTIN_COMM_ARG_OFF 1

#endif
