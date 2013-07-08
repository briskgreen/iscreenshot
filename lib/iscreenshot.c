#include "iscreenshot.h"

void error_quit(const char *msg)
{
	perror(msg);
	exit(-1);
}
