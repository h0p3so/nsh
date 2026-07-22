#include "post.h"
#include "builtin.h"

bool post_is_builtin (const struct LexToken *stream)
{
	const struct BuiltInCmd *cmd = builtin_get(head->source, head->length);

	if (cmd == NULL)
	{ return false; }

	cmd->run(head, NULL);
	return true;
}

bool post_is_external (const struct LexToken *stream)
{
	return false;
}
