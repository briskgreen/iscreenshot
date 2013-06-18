#include "iscreenshot.h"

void error_quit(const char *msg)
{
	prror(msg);
	exit(-1);
}
