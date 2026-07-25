#include "libs/stdv.h"
#include "comm.h"
#include "pwd.h"
#include "cd.h"

// this file only process the argument given to `cd` command, the
// file that actually changes the directory is `pwd`

void builtin_cd_cmd_run (const struct ParserTreeCmd *treeCmd)
{
	if (stdv_size(treeCmd->commandRelated.argv) == NSH_BUILTIN_COMM_ARG_OFF)
	{ builtin_pwd_go_home(); return; }
}
