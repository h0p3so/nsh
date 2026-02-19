#include "post.h"
#include "builtin/builtin.h"

bool post_is_builtin (const struct LexToken *head)
{
	struct BuiltInCmd *cmd = builtin_get(head->source, head->length);
	return (cmd) ? true : false;
}

bool post_is_external (const struct LexToken *head)
{
	return false;
}
